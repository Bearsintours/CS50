# import
import sys
from cs50 import get_string

# usage: program key
if len(sys.argv) != 2:
    print("Please enter valid key")
    exit(code=1)

# check if every char of the key is a letter
for j in range(len(sys.argv[1])):
    if sys.argv[1][j].isalpha() == False:
        print("Please enter valid key")
        exit(code=1)

# get key and key length
keys = sys.argv[1]
keys_length = len(keys)

# prompt user for plaintext
print("plaintext: ", end="")
p = get_string()
l = len(p)

print("ciphertext: ")

# iterate over each character in plaintext
for i in range(len(p)):

    # for each letter get the key
    k = keys[i % keys_length]
    k = ord(k.lower()) - 97

    # if lowercase
    if ord(p[i]) >= 97 and ord(p[i]) <= 122:
        index = ord(p[i]) - 97
        c = chr(97 + (index + k) % 26)
        print(c, end="")

    # if uppercase
    elif ord(p[i]) >= 65 and ord(p[i]) <= 90:
        index = ord(p[i]) - 65
        c = chr(65 + (index + k) % 26)
        print(c, end="")

    # if nonalpha
    else:
        print(p[i], end="")

# new line
print()
