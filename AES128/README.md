This work was done by Farhan Almufleh, Tanvi Mehta, and Vi Nguyen. Vi wrote the pseudocode, and the three of us implemented it.

## Project Task
The purpose of this project is to write a program that will run an exhaustive search attack on a AES block cipher with a key space effectively limited to 24 bits. Specifically, the key has the following format (in hex): 80 00 ... 00 XX XX XX, where “X” denotes an arbitrary hex number. In other words, the first 13 bytes of the key are fixed to be zeroes (except that the first bit is fixed to be “1”), and the last 3 bytes can be arbitrary (so that they need to be checked by the exhaustive search). Our task was to find the key which matches the provided three plaintext-ciphertext pairs. The plaintexts are given as the files “m1.txt”, “m2.txt”, and “m3.txt”, the respective ciphertexts are in the files “c1.bin”, “c2.bin”, and “c3.bin”, and the respective nonces are in the files “nonce1.bin”, “nonce2.bin”, and “nonce2.bin”. We use the exhaustive search algorithm to crack it.

## Project Description:
Setup_demo.py was given to us to show how the plaintext and ciphertext were generated. Since we’ll submit all binary files together with python files in the same zip folder, we updated setup_demo.py file to have the appropriate file path. Our solution is provided in solution.py file. The solution.py program starts the same way as the setup_demo.py program. It defines the length of the postfix key to be 24 bits. It then reads the given plaintext, nonce, and ciphertext files. Then it attempts to generate the key: since the last 3 bytes of key in hex was generated randomly by setup_demo.py, the program has to generate up to 2^24 different keys before it can find the right one. Then it loops through all these keys. On each loop, the program decrypts the ciphertext 1 with the key and the corresponding nonce and compares the freshly decrypted message with the message 1 that was read from the binary file to find the right key. If the two messages match, it then uses the key to decrypt ciphertext 2 and 3 using their corresponding nonces. If the outputs of these match the given plaintexts 2 and 3 respectively, the program outputs the key to a text file and breaks the loop. Since the project requires us to output the key in hexadecimal, we created a new function in utils.py to convert binary to decimal, then convert from decimal to hexadecimal. Utils.py also uses other methods that were given to us in utils_demo.py. It took roughly 5 -7 minutes for solution.py to find the correct key.

To run and compile, do *python solution.py*.

## Project Output
The key for given m1, m2, m3 and c1, c2, c3 attached in this directory that we found by running our program is: 0x800000000000000000000000007e8fd2

- Output key in hex by running solution.py:  
<img src="https://user-images.githubusercontent.com/70772170/129394554-2adc97e3-dddf-49ca-930a-9eef92442e8f.png" width="300" height="150">  

- Output key in binary:  
<img src="https://user-images.githubusercontent.com/70772170/129394964-9e5e2a4e-534a-4042-8b9d-d97853856407.png" width="600" height="150">  

- Output of program:  
<img src="https://user-images.githubusercontent.com/70772170/129395185-39d84077-6c1f-452a-9761-afbb05a4782b.png" width="800" height="100">



