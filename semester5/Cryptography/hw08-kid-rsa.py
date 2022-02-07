#!/usr/bin/python3

class KIDRSA:
    def __init__(self, mode: str):
        if mode == "E":
            self.encrypt()
        elif mode == "D":
            self.decrypt()

    def encrypt(self):
        num = input("Input 4 integers a, b, a', b' -- ").split(" ")
        if len(num) != 4:
            raise Exception("Please input '4' integers")
        a, b, a1, b1 = (int(n) for n in num)
        m = a * b - 1
        e = a1 * m + a
        d = b1 * m + b
        n = (e * d) // m
        print("You may publish your public key (n,e) = ({},{})".format(n, e))
        print("and keep your private key (n,d) = ({},{}) secret.".format(n, d))
        message = input("Plaintext - ")
        cipher_text = []
        for m in message:
            cipher_text.append(ord(m) * e % n)
        print(*cipher_text)

    def decrypt(self):
        key = input("Your private key (n, d), separated by a space or comma -- ").replace(", ", " ").replace(",", " ").split(" ")
        if len(key) != 2:
            raise Exception("Please input '2' keys")
        n, d = (int(k) for k in key)
        cipher_text = [int(i) for i in input("Ciphertext (integers separated by spaces) -- ").split(" ")]
        message = []
        for c in cipher_text:
            message.append(c * d % n)
        print(*message)
        print("Plaintext - {}".format("".join([chr(m) for m in message])))

def main():
    mode = input("[E]ncryption, [D]ecryption, or [Q]uit -- ").upper()
    KIDRSA(mode)

if __name__ == "__main__":
    main()
