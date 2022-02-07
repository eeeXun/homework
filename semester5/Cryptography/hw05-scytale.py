#!/usr/bin/python3
import sys
from random import randint
from math import ceil

def scytal_help():
    print("Usage:")
    print("echo [MESSAGE] | [./hw05-encrypt|./hw05-decrypt] key")

class Scytal:
    def __init__(self, key: int, msg: str):
        self.row = key
        self.msg = msg
        self.msg_len = len(self.msg)
        self.col = ceil(self.msg_len / self.row)
        self.result = ""

    def encrypt(self):
        for i in range(self.col):
            for j in range(self.row):
                index = i + (j * self.col)
                if index >= self.msg_len:
                    self.result += self.rand_chr()
                else:
                    self.result += self.msg[index]
        self.print_result()

    def decrypt(self):
        for i in range(self.row):
            for j in range(self.col):
                index = i + (j * self.row)
                self.result += self.msg[index]
        self.print_result()

    def rand_chr(self):
        return chr(randint(65, 91))

    def print_result(self):
        print(self.result)

if __name__ == "__main__":
    mode = sys.argv[0]
    if ("hw05-encrypt" not in mode and "hw05-decrypt" not in mode) or len(sys.argv) != 2:
        scytal_help()
        exit(1)
    else:
        key = int(sys.argv[1])
    message = ""
    for line in sys.stdin:
        message += line.replace(" ", "").replace("\n", "").upper()
    # encrypt / decrypt
    cipher = Scytal(key, message)
    if "hw05-encrypt" in mode:
        cipher.encrypt()
    elif "hw05-decrypt" in mode:
        cipher.decrypt()
