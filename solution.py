#BIRTHDAY ATTACK
#MESSAGE SIZE = 256 block

from random import randint
import hashlib

# Declare array
arr = [[], []]

for i in range(2):  # attack only need to runs at most 2 times

    # Save 2^20 random inputs and their BadHash40 outputs in arr
    for i in range(1, 11):  # TODO actual range will be 1 to 2 ** 20 + 1

        # Get a random 256 bit number
        x = randint(0, 21) # TODO actual range will be 0 to 2 ** 256
        arr[0].append(x)

        # Perform BadHash40
        y = hashlib.sha256(
            str(x)
        )  # TODO I don't think this is taking only the first 40 bits!!
        arr[1].append(y)

    print("Before sort: ", str(arr)) # TESTING - remove when done!!
    
    # Sort the outputs from smallest to largest
    arr[1].sort() # TODO update sort
    
    print("After sort: ", str(arr)) # TESTING - remove when done!!

    #look for the first 2 inputs that give out duplicate outputs
    for i in range (len(arr[1])-1):
        if arr[1][i] == arr[1][i+1]:
            print("found pairs of input {" + hex(arr[0][i]) + ", " + hex(arr[0][i+1]) + "} that has the same output as " + arr[1][i].hexdigest())
            break
