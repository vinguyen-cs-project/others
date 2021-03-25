from random import randint
import hashlib

input1 = 1  # TODO remove later

# Declare array
arr = [[], []]

# Assign first row to input and second row to output
inputRow = arr[0]
outputRow = arr[1]

while input1 != 2:  # TODO change condition

    # Save 2^20 random inputs and their BadHash40 outputs in arr
    for i in range(1, 10):  # TODO actual range will be 1 to 2 ** 20

        # Get a random 256 bit number
        x = randint(0, 2 ** 256)  # TODO shouldn't this be 2 ** 256 - 1?
        inputRow.append(x)

        # Perform BadHash40
        y = hashlib.sha256(
            str(x)
        )  # TODO I don't think this is taking only the first 40 bits!!
        outputRow.append(y)

    # Sort the outputs from smallest to largest
    outputRow.sort()

    input1 = 2  # TODO remove later

print("final array: " + str(arr))  # TODO remove later
