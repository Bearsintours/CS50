# import get_int from cs50 library
from cs50 import get_int

# prompt user for int between 0 and 23
while True:
    print("Pyramid height")
    height = get_int()
    if(height >= 0 and height <= 23):
        break

# for each row
for i in range(height):

    # print spaces
    spaces = height - 1
    while spaces > i:
        print(" ", end="")
        spaces -= 1

    # print blocks first pyramid
    blocks = 0
    while blocks <= i:
        print("#", end="")
        blocks += 1

    # print spaces between 2 pyramids
    print("  ", end="")

    # print block second pyramid
    blocks = 0
    while blocks <= i:
        print("#", end="")
        blocks += 1

    # new line after each row
    print()
