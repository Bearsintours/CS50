# import get_float from cs50 library
from cs50 import get_float

# prompt user for positive value
while True:
    print("What is the change owed?")
    change = get_float()

    # keep prompting user until we get a positive value
    if(change > 0):
        break

# multiply change by 100 to work with non decimal values
change = round(change * 100)
coins = 0

# count quarters until change < 25
while(change >= 25):

    # keep track of coins given and update change
    coins += 1
    change -= 25

# count dimes until change < 10
while(change >= 10):

    # keep track of coins given and update change
    coins += 1
    change -= 10

# count five cents until change < 5
while(change >= 5):

    # keep track of coins given and update change
    coins += 1
    change -= 5

# count cents until change = 0
while(change >= 1):

    # keep track of coins given and update change
    coins += 1
    change -= 1

# print minimum number of coins required to give a user change.
print(coins)
