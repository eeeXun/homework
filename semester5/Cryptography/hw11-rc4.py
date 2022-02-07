#!/usr/bin/python3
import sys
S_SIZE = 256

def rc4_help():
    print("Usage:")
    print("echo [MESSAGE] | [./hw11-encrypt|./hw11-decrypt] key")

class RC4:
    def __init__(self):
        self.s = [i for i in range(S_SIZE)]
        self.key_stream = []
        self.result_a = ""  # ascii for result
        self.result_d = []  # decimal array for result
        self.result_x = ""  # hex str for result

    def encrypt(self, key, message):
        key_int = self.stoi(key)
        m_int = self.stoi(message)
        self.shuffle_s(key_int)
        self.gen_key_stream(len(m_int))
        self.xor(m_int)
        self.result_x = self.dtox(self.result_d)
        print(self.result_x)

    def decrypt(self, key, message):
        key_int = self.stoi(key)
        m_int = self.xtod(message)
        self.shuffle_s(key_int)
        self.gen_key_stream(len(m_int))
        self.xor(m_int)
        self.result_a = self.dtos(self.result_d)
        print(self.result_a)

    def stoi(self, s):
        """
        str to int array
        """
        return [ord(i) for i in s]

    def dtox(self, arr):
        """
        int array to hex(str)
        """
        x = ""
        for i in arr:
            x += "{:0>2X}".format(i)
        return x

    def xtod(self, s):
        """
        hex(str) to int array
        """
        d = []
        for i in range(len(s) // 2):
            d.append(int(s[i * 2], 16) * 16 + int(s[i * 2 + 1], 16))
        return d

    def dtos(self, arr):
        """
        int array to str
        """
        s = ""
        for i in arr:
            s += chr(i)
        return s

    def shuffle_s(self, key_int):
        j = 0
        for i in range(len(self.s)):
            j = (j + self.s[i] + key_int[i % len(key_int)]) % len(self.s)
            self.s[i], self.s[j] = self.s[j], self.s[i]

    def gen_key_stream(self, size_m):
        i = 0
        j = 0
        for k in range(size_m):
            i = (i + 1) % len(self.s)
            j = (j + self.s[i]) % len(self.s)
            self.s[i], self.s[j] = self.s[j], self.s[i]
            t = (self.s[i] + self.s[j]) % len(self.s)
            self.key_stream.append(self.s[t])

    def xor(self, m_int):
        for i in range(len(m_int)):
            self.result_d.append(m_int[i] ^ self.key_stream[i])

def main():
    mode = sys.argv[0]
    if ("hw11-encrypt" not in mode and "hw11-decrypt" not in mode) or len(sys.argv) != 2:
        rc4_help()
        exit(1)
    else:
        key = sys.argv[1]
    message = input()
    rc4 = RC4()
    if "hw11-encrypt" in mode:
        rc4.encrypt(key, message)
    elif "hw11-decrypt" in mode:
        rc4.decrypt(key, message)

if __name__ == "__main__":
    main()
