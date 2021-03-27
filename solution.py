# BIRTHDAY ATTACK
# MESSAGE SIZE = 256 block

from random import randint
import hashlib
import numpy as np

# Declare array
arr = np.empty((2, 0), int)

found = False
for i in range(2):  # attack only need to runs at most 2 times

    # Save 2^20 random inputs and their BadHash40 outputs in arr
    for i in range(1, 2**20+1):  # TODO actual range will be 1 to 2 ** 20 + 1

        # Get a random 256 bit number
        x = randint(0, 2**256-1)  # TODO actual range will be 0 to 2 ** 256 - 1
        # arr[0].append(x) # TODO remove

        # Perform BadHash40
        y = hashlib.sha256(str(x))
        #        print(y.hexdigest()) # TESTING - remove later

        col = [x, y.hexdigest()[0:10]]
        print(col)
        arr = np.append(arr, np.array([col]).transpose(), axis=1)
        # arr[1].append(y.hexdigest()[0:10]) #TODO remove

    print("Before sort: ", arr)  # TESTING - remove when done!!

    # Sort the outputs from smallest to largest

    sortedArr = arr[:, arr[1].argsort()]
    # arr[1].sort()  # TODO update sort to make sure first row indicies correspond with second row indices

    print("After sort: ", sortedArr)  # TESTING - remove when done!!

    # look for the first 2 inputs that give out duplicate outputs
    for i in range(len(sortedArr[1]) - 1):
        if sortedArr[1][i] == sortedArr[1][i + 1]:
            print(
                "found pairs of input {" +
                hex(sortedArr[0][i])+ ", "+
                hex(sortedArr[0][i + 1])
                +
                "} that has the same output as "
                + (sortedArr[1][i])
            )
            found = True
            break
    if found == True:
        break
    
