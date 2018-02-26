from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure responses aren't cached


@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    """Show portfolio of stocks"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure user enters amount
        if not request.form.get("cash"):
            return apology("Please enter amount", 403)

        # Ensure amount is a positive integer
        elif not int(request.form.get("cash")) > 0 or not request.form.get("cash").isdigit():
            return apology("Please enter valid amount", 403)

        # Update user's cash balance
        else:
            db.execute("UPDATE users SET cash = cash + :cash_added WHERE id = :id",
                       cash_added=request.form.get("cash"), id=session["user_id"])

        # Redirect user to home page
        return redirect("/")

    else:

        # Query database for user's portfolio
        rows = db.execute("SELECT * FROM portfolio WHERE id=:id", id=session["user_id"])

        # Store stocks info in list to render in index.html
        index = []
        total_value = 0
        for row in rows:
            symbol = row['stock']
            stock = lookup(symbol)
            price = stock['price']
            shares = row['shares']
            value = price * shares
            total_value += value
            index.append([symbol, usd(price), shares, usd(value)])

        # Query database for cash balance
        cash = db.execute("SELECT cash FROM users WHERE id=:id", id=session["user_id"])
        cash_balance = cash[0]['cash']

        # Calculate grand total (stocks total value + cash)
        grand_total = usd(total_value + cash_balance)
        cash_available = usd(cash_balance)

        # render portfolio
        return render_template("index.html", cash_available=cash_available, grand_total=grand_total, stocks=index)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure stock name was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock", 400)

        # Ensure shares number was submitted
        elif not request.form.get("shares") or not request.form.get("shares").isdigit() or int(request.form.get("shares")) <= 0:
            return apology("must enter positive number of shares", 400)

        # Use lookup function to get stock info
        stock = lookup(request.form.get("symbol"))

        # Ensure stock is found,
        if stock == None:
            return apology("We could not find this stock")

        # Get user id, order amount and cash available
        else:
            id = session["user_id"]
            shares = request.form.get("shares")
            symbol = request.form.get("symbol")
            order = stock['price'] * float(shares)
            cash = db.execute("SELECT cash FROM users WHERE id = :id", id=id)
            cash_available = cash[0]['cash']

            # Ensure user has enough cash for transaction
            if float(cash_available) - order < 0:
                return apology("Insufficient funds")

            # Update users table and transactions table
            else:

                # Update cash in users table
                db.execute("UPDATE users SET cash = :cash_available - :order WHERE id = :id",
                           cash_available=cash_available, order=order, id=id)

                # Query database for stock bought
                rows = db.execute(
                    "SELECT * FROM portfolio WHERE id=:id AND stock=:stock", id=id, stock=symbol)

                # If stock is not in portfolio, insert stock
                if len(rows) == 0:
                    db.execute("INSERT INTO portfolio (id, stock, shares) VALUES (:id, :stock, :shares)",
                               id=id, stock=symbol, shares=shares)

                # If stock already in portfolio, update number of shares
                else:
                    db.execute("UPDATE portfolio SET shares = shares + :shares WHERE id=:id AND stock=:stock",
                               shares=shares, id=id, stock=symbol)

                # # Insert id, stock, number of shares and price into history table
                db.execute("INSERT INTO history (id, stock, shares, price) VALUES (:id, :stock, :shares, :price)",
                           id=id, stock=symbol, shares=shares, price=usd(stock['price']))

                # Redirect user to home page
                return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # Query database for user's transaction history
    transactions = db.execute("SELECT * FROM history WHERE id=:id", id=session["user_id"])

    # Create emply list and append transaction info for display in history.html
    history = []
    for transaction in transactions:
        date = transaction['date']
        symbol = transaction['stock']
        price = transaction['price']
        shares = transaction['shares']
        history.append([date, symbol, price, shares])

    # Render history.html
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Use lookup function to get stock info
        quote = lookup(request.form.get("symbol"))

        # If symbol exists, get name, price and symbol
        if not quote == None:

            name = quote['name']
            price = usd(quote['price'])
            symbol = quote['symbol']

            # displays stock info
            return render_template("stock.html", name=name, price=price, symbol=symbol)

        # If symbol not found, return apology
        return apology("We could not find this stock")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("Missing username!", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("Missing password!", 400)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("Please confirm your password", 400)

        # Ensure both passwords entered are identical
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("You entered 2 different passwords...", 400)

        # Hash password to store it in db
        hash = generate_password_hash(request.form.get("password"))

        # Insert username and hashed password into db
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)",
                            username=request.form.get("username"), hash=hash)

        if not result:
            return apology("Username already exists", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure stock name was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock", 403)

        # Ensure positive number of shares was submitted
        if not request.form.get("shares") or not request.form.get("shares").isdigit() or int(request.form.get("shares")) <= 0:
            return apology("must provide positive number of shares", 403)

        # Query database for stock
        rows = db.execute("SELECT * FROM portfolio WHERE id = :id AND stock = :stock",
                          id=session['user_id'], stock=request.form.get('symbol'))

        # Ensure users has enough shares
        if rows[0]['shares'] < float(request.form.get('shares')):
            return apology("Unsufficient number of shares available")

        # Get stock value and transaction amount
        symbol = request.form.get('symbol')
        stock = lookup(symbol)
        id = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=id)
        cash_balance = cash[0]['cash']
        stock_value = stock['price']
        shares = float(request.form.get('shares'))
        sale = stock_value * float(shares)

        # Update cash in users table
        db.execute("UPDATE users SET cash = :cash_balance + :sale WHERE id = :id",
                   cash_balance=cash_balance, sale=sale, id=id)

        # Delete stock from portfolio if 0 shares left
        if rows[0]['shares'] - shares == 0:
            db.execute("DELETE FROM portfolio WHERE id = :id AND stock = :stock", id=id, stock=symbol)

        # Update number of shares in portfolio
        else:
            db.execute("UPDATE portfolio SET shares = shares - :shares WHERE id=:id AND stock=:stock",
                       shares=shares, id=id, stock=symbol)

        # Insert id, stock, number of shares and price into history table
        db.execute("INSERT INTO history (id, stock, shares, price) VALUES (:id, :stock, :shares, :price)",
                   id=id, stock=symbol, shares=-(shares), price=usd(stock['price']))

        # Redirect user to home page
        return redirect("/")

    # Render sell.html
    else:

        # Query db for all stock symbol owned
        stocks = db.execute("SELECT stock FROM portfolio WHERE id=:id", id=session["user_id"])

        # Make a list of all stock to render in select field
        symbols = []
        for symbol in stocks:
            symbols.append(symbol['stock'])

        # Render sell.html
        return render_template("sell.html", symbols=symbols)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
