# import
import crypt
import sys

# prompt user for hashed password
if len(sys.argv) != 2:
    print("Please enter valid password")
    exit(code=1)

# store hashed password
hashed = sys.argv[1]

# create string with every letters of the alphabet lowercase and uppercase
letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

# iterate over letters in 4 loops to get all combination possible
for i in letters:
    str = i

    for j in letters:
        str = i + j

        for k in letters:
            str = i + j + k

            for l in letters:
                str = i + j + k + l

                # print password if found
                if hashed == crypt.crypt(str, "50"):
                    print(f"Password: {str}")
                    exit(code=0)
