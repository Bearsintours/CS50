# import
import sys
from cs50 import get_string

# usage: program key
if (len(sys.argv) != 2):
    print("Please enter valid key")
    exit(code=1)

# get key as an integer
k = int(sys.argv[1])

# prompt user for plaintext
print("plaintext: ", end="")
plaintext = get_string()

print("ciphertext: ", end="")

# iterate over each character in plaintext
for c in plaintext:

    # if lowercase
    if (ord(c) >= 97 and ord(c) <= 122):
        index = ord(c) - 97
        c = chr(97 + (index + k) % 26)

        # print ciphertext char
        print(c, end="")

    # if uppercase
    elif (ord(c) >= 65 and ord(c) <= 90):
        index = ord(c) - 65
        c = chr(65 + (index + k) % 26)

        # print ciphertext char
        print(c, end="")

    # print same if nonalpha
    else:
        print(c, end="")

# new line
print()
