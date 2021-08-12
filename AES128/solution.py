# PROJECT 1
# BRUTE FORCE ATTACK
# Vi Nguyen, Tanvi Mehta, Farhan Almufleh

import json
from base64 import b64encode, b64decode
from Crypto.Cipher import AES
from Crypto.Util.Padding import pad, unpad
import time
import argparse
from random import randint
from utils import *

if __name__ == "__main__":

    parser = argparse.ArgumentParser(
        description="Setup for Bruteforce attack against randomized AES-128-CTR."
    )
    parser.add_argument(
        "-n", type=int, help="Effective key length in bytes.", default=3
    )
    parser.add_argument(
        "-m1", type=str, help="Plaintext1 file input name.", default="m1.txt"
    )
    parser.add_argument(
        "-m2", type=str, help="Plaintext2 file input name.", default="m2.txt"
    )
    parser.add_argument(
        "-m3", type=str, help="Plaintext3 file input name.", default="m3.txt"
    )

    args = parser.parse_args()
    # number of bits that represent size of key space XX XX XX.
    length_postfix = args.n * 8
    # Reading plaintexts from files.
    plaintext1 = read_file(fn=args.m1).encode()
    plaintext2 = read_file(fn=args.m2).encode()
    plaintext3 = read_file(fn=args.m3).encode()
    # Reading nonce from binary files.
    nonce1 = read_bytes(fn="nonce1.bin")
    nonce2 = read_bytes(fn="nonce2.bin")
    nonce3 = read_bytes(fn="nonce3.bin")
    # Reading ciphertext from binary files.
    ctxt1 = read_bytes(fn="c1.bin")
    ctxt2 = read_bytes(fn="c2.bin")
    ctxt3 = read_bytes(fn="c3.bin")

    # initialize starting range for guessing key value XX XX XX
    postfix_key = 0
    # initialize ending range for guessing key value XX XX XX
    last_postfix = 2 ** length_postfix - 1

    print("Please wait. Searching for key...")
    # loop till finding the right key
    while postfix_key <= last_postfix:
        # Defining key for decryption.
        main_key = bin(2 ** 127 + postfix_key)

        # decrypt ciphertext
        txt1 = decryptor_CTR(ctxt=ctxt1, nonce=nonce1, key=bitstring_to_bytes(main_key))
        # compare new plaintext to plaintext from files
        if txt1 == plaintext1:
            txt2 = decryptor_CTR(
                ctxt=ctxt2, nonce=nonce2, key=bitstring_to_bytes(main_key)
            )
            txt3 = decryptor_CTR(
                ctxt=ctxt3, nonce=nonce3, key=bitstring_to_bytes(main_key)
            )
            if (txt2 == plaintext2) and (txt3 == plaintext3):
                print("Key in hex is outputted to key.txt file")
                # output key in hex to txt file
                write_file("key.txt", bit_to_hex(main_key))
                break

        postfix_key += 1
