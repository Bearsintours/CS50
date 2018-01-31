# import get_long from cs50 library
from cs50 import get_float

# prompt user for a positive number
while True:
    print("Enter credit card number: ")
    cc_num = get_float()

    # keep prompting user until we get a positive value
    if(cc_num > 0):
        break

# declare variables to keep track of digits and number of digits
digits = 0
other_digits = 0
count = 0

# starting with the number’s second-to-last digit:
i = cc_num // 10
while i > 0:

    # get every other digit and mutliply it by 2
    digit = i % 10
    num = digit * 2

    # if number is more than 9, add 2 digits of number
    if num > 9:
        num = num % 10 + ((num // 10) % 10)

    # sum those digits
    digits += num
    i = i // 100

# add that sum to the sum of the digits that weren’t multiplied by 2:
j = cc_num
while j > 0:
    other_digits += j % 10
    j = j // 100

# add 2 sums
result = digits + other_digits

# if last digit of that sum is 0, card is legit
if result % 10 == 0:

    # since card is valid, check if card is AMEX, MASTERCARD or VISA
    k = cc_num
    while k > 0:
        # count digits
        count += 1

        # get first 2 digits
        if k >= 10 and k < 100:
            first2_digits = k

        # get first digit
        if k < 10:
            first_digit = k

        k = k // 10

    # is it an AMEX?
    if count == 15 and (first2_digits == 34 or first2_digits == 37):
        print("AMEX")

    # is it an MASTERCARD?
    elif count == 16 and first2_digits >= 51 and first2_digits <= 55:
        print("MASTERCARD")

    # is it a VISA?
    elif (count == 13 or count == 16) and first_digit == 4:
        print("VISA")

    # if none of the above, it is an invalid card
    else:
        print("INVALID")

# if last digit is not 0, card is invalid
else:
    print("INVALID")
