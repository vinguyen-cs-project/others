# BIRTHDAY ATTACK ON BADHASH40
# MESSAGE SIZE = 256 block
# BADHASH40 = first 40 bits of sha256 hash
# Tanvi Mehta, Farhan Almufleh and Vi Nguyen

from random import randint
from sort import *
import hashlib
from utils_demo import *

# Declare array
arr = [[], []]
# value to check when found duplicate output
found = False

for i in range(2):  # attack only need to runs at most 2 times
    print("Generating input and hashing them...")
    # Save 2^20 random inputs and their BadHash40 outputs in arr
    for i in range(1, 2 ** 20 + 1):

        # Get a random 256 bit number
        x = randint(0, 2 ** 256 - 1)
        arr[0].append(hex(x))

        # Perform BadHash40
        y = hashlib.sha256(str(x))
        arr[1].append(y.hexdigest()[0:10])

    print("Sorting through the array...")
    heapSort(arr)

    print("Looking for duplicate output")
    # look for the first 2 inputs that give out duplicate outputs
    for i in range(len(arr[1]) - 1):
        if arr[1][i] == arr[1][i + 1]:
            print(
                "found pairs of input {"
                + arr[0][i]
                + ", "
                + arr[0][i + 1]
                + "} that has the same output "
                + (arr[1][i])
            )
            found = True
            break
    if found == True:
        break
    print("\n")

print("Writing inputs and hash outputs to file...")
with open("hash.txt", "w") as output:
    output.write("input, output:")

for i in range(len(arr[1])):
    with open("hash.txt", "a") as output:
        output.write(arr[0][i] + ", " + arr[1][i])
