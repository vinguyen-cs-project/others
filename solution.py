from random import randint
import hashlib

# rows, cols = (2, 11)
# arr = [[0] * cols] * rows
# arr = []
# arr.append([])

# arr.insert(0, 1)

# arr[0].append(222)
# arr[1].append(1)
# print[arr]
input1 = 1  # remove later

arr = [[], []]

firstrow = arr[0]
secondrow = arr[1]


while input1 != 2:  # change condition
    for i in range(1, 10):  # 2 ** 20 - 1):
        x = randint(0, 2 ** 256)
        firstrow.append(x)
        y = hashlib.sha256(str(x))
        secondrow.append(y)
    secondrow.sort()
    # print("row0, loop " + str(i) + ": " + str(arr))
    # print()
    # y = 0  # hashlib.sha256() #y = perform bad hash 40
    # arr[1][i] = 1
    # print("row 1, loop " + str(i) + ": " + str(arr))
    # print(arr)  # remove later
    input1 = 2  # remove later"""


print("final array: " + str(arr))
