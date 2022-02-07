#!/usr/bin/python3
from random import randint

class Merkle:
    # prompt
    prompt_n = "Select the block size.\nn? "
    prompt_w = "Input a list of n superincreasing integers, separated by commas or spaces.\nIf you simply press <ENTER>, we shall randomly generate one for you.\nW? "
    prompt_b = "Input a list of n integers, separated by commas or spaces.\nB? "
    prompt_q = "Please input an integer larger than {}\nq? "
    prompt_r = "Please input an integer which is relatively prime with q.\nr? "
    prompt_ciphertext = "Input ciphertext (separated by commas or spaces) - "

    def __init__(self, mode: str):
        if mode == "K":
            self.fn_key()
        elif mode == "E":
            self.fn_encrypt()
        elif mode == "D":
            self.fn_decrypt()

    def fn_key(self):
        n = int(input(self.prompt_n))
        w = input(self.prompt_w)
        if not w:
            w = self.auto_W(n)
            print("Random W:", *w)
        else:
            w = [int(i) for i in w.replace(",", "").split(" ")]
        status_w = self.check_W(w, n)
        q = int(input(self.prompt_q.format(status_w)))
        r = int(input(self.prompt_r))
        if self.gcd(q, r) != 1:
            raise Exception("r is not relatively prime with q.")
        b = []
        for i in range(n):
            b.append((r * w[i]) % q)
        print("=========================")
        print("Announce your public key:")
        print("n =", n)
        print("B =", b)
        print("q =", q)
        print("=========================")

    def fn_encrypt(self):
        n = int(input("n? "))
        b = [int(i) for i in
                input(self.prompt_b).replace(",", "").split(" ")]
        self.check_B(b, n)
        q = input("q? ")
        # text in string with binary form
        text = ["{0:b}".format(ord(i)) for i in
                input("Plaintext - ")]
        ciphertext = []
        for i in range(len(text)):
            sum = 0
            for j in range(len(text[i])):
                sum += int(text[i][len(text[i]) - j - 1]) * b[len(b) - j - 1]
            ciphertext.append(sum)
        print("Ciphertext:", ciphertext)

    def fn_decrypt(self):
        n = int(input(self.prompt_n))
        w = input(self.prompt_w)
        if not w:
            w = self.auto_W(n)
        else:
            w = [int(i) for i in w.replace(",", "").split(" ")]
        status_w = self.check_W(w, n)
        q = int(input(self.prompt_q.format(status_w)))
        r = int(input(self.prompt_r))
        if self.gcd(q, r) != 1:
            raise Exception("r is not relatively prime with q.")
        inverse = pow(r, -1, q)
        ciphertext = [int(i) for i in
                input(self.prompt_ciphertext).replace(",", "").split(" ")]
        text_int = []
        text_str = ""
        for i in range(len(ciphertext)):
            tmp = ciphertext[i] * inverse % q
            tmp_result = 0
            for j in range(len(w)):
                if tmp == 0:
                    break
                elif tmp >= w[len(w) - j - 1]:
                    tmp_result += 2 ** j
                    tmp -= w[len(w) - j - 1]
            text_int.append(tmp_result)
            text_str += chr(tmp_result)
        print("Plaintext:", *text_int)
        print(text_str)

    def check_W(self, arr: list, size: int):
        if len(arr) != size:
            raise Exception("Please input {} numbers".format(size))
        return sum(arr)

    def check_B(self, arr: list, size: int):
        if len(arr) != size:
            raise Exception("Please input {} numbers".format(size))

    def auto_W(self, size: int):
        w = []
        for i in range(size):
            w.append(sum(w) + randint(1, 10))
        return w

    def gcd(self, a: int, b: int):
        if a == 0:
            return b
        elif b == 0:
            return a
        else:
            return self.gcd(b, a % b)

def main():
    mode = input("[K]ey generation / [E]ncryption / [D]ecryption? ").upper()
    Merkle(mode)

if __name__ == "__main__":
    main()
