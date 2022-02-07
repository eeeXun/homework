#!/usr/bin/python3
from random import sample

class RSA:
    prime = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]
    prompt_prime = "Select two prime numbers from the above, separated by a space.\nOr press ENTER and I'll randomly select two for you -- "

    def __init__(self, mode: str):
        if mode == "E":
            self.encrypt()
        elif mode == "D":
            self.decrypt()

    def encrypt(self):
        for i in range(5):
            print("\t".join([str(i) for i in self.prime[i * 5: i * 5 + 5]]))
        my_prime = input(self.prompt_prime)
        if not my_prime:
            my_prime = sample(self.prime, 2)
        else:
            my_prime = [int(i) for i in my_prime.split(" ")]
        self.check_my_prime(my_prime)
        print("The two prime numbers are {} and {}.".format(*my_prime))
        n = my_prime[0] * my_prime[1]
        print("n = {} * {} = {}".format(*my_prime, n))
        euler_n = max(my_prime) - 1
        possible_e = self.coprime_n(euler_n)
        print("Possible values of e which are coprime to {}:".format(euler_n))
        print("\t".join([str(i) for i in possible_e]))
        e = int(input("Choose one -- "))
        if e not in possible_e:
            raise Exception("Please choose from above")
        d = pow(e, -1, euler_n)
        print("You may publish your public key (n,e) = ({},{})".format(n, e))
        print("and keep your private key (n,d) = ({},{}) secret.".format(n, d))
        message = input("Plaintext - ")
        cipher_text = []
        for m in message:
            cipher_text.append(pow(ord(m), e) % n)
        print(*cipher_text)

    def decrypt(self):
        key = input("Your private key (n, d), separated by a space or comma -- ").replace(", ", " ").replace(",", " ").split(" ")
        if len(key) != 2:
            raise Exception("Please input '2' keys")
        n, d = (int(k) for k in key)
        cipher_text = [int(i) for i in input("Ciphertext (integers separated by spaces) -- ").split(" ")]
        message = []
        for c in cipher_text:
            message.append(pow(c, d) % n)
        print(*message)
        print("Plaintext - {}".format("".join([chr(m) for m in message])))

    def check_my_prime(self, arr: list[int]):
        if len(arr) != 2:
            raise Exception("Please input '2' prime numbers")
        for i in arr:
            if i not in self.prime:
                raise Exception("Please input 2 prime numbers 'from above'")

    def coprime_n(self, euler_n: int):
        result = []
        for i in range(2, euler_n):
            if self.gcd(euler_n, i) == 1:
                result.append(i)
        return result

    def gcd(self, a: int, b: int):
        if a == 0:
            return b
        elif b == 0:
            return a
        else:
            return self.gcd(b, a % b)

def main():
    mode = input("[E]ncryption, [D]ecryption, or [Q]uit -- ").upper()
    RSA(mode)

if __name__ == "__main__":
    main()
