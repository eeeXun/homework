#!/usr/bin/python3
import sys

baudot_table = { "A": "11000", "B": "10011", "C": "01110", "D": "10010",
        "E": "10000", "F": "10110", "G": "01011", "H": "00101", "I": "01100",
        "J": "11010", "K": "11110", "L": "01001", "M": "00111", "N": "00110",
        "O": "00011", "P": "01101", "Q": "11101", "R": "01010", "S": "10100",
        "T": "00001", "U": "11100", "V": "01111", "W": "11001", "X": "10111",
        "Y": "10101", "Z": "10001", "4": "01000", "3": "00010", "9": "00100",
        "8": "11111", "+": "11011", "/": "00000",
}
baudot_reverse = {int(y, 2): x for x, y in baudot_table.items()}

chi_str = "N4LNFUWKHGR9ZD4/VMQ4BYH"
chi_wheel = [baudot_table[i] for i in chi_str]
mu_str = "0010111110001"
mu_wheel = [i for i in mu_str]
psi_str = "PNTKTUGFLFLX4NAOIB4"
psi_wheel = [baudot_table[i] for i in psi_str]

class Lorenz:
    def __init__(self):
        mode = sys.argv[0]
        if "hw04-encrypt" not in mode and "hw04-decrypt" not in mode:
            self.lorenz_help()
            exit(1)
        self.chi = sys.argv[1]
        self.mu = sys.argv[2]
        self.psi = sys.argv[3]
        self.message = ""
        for line in sys.stdin:
            self.message += line.replace(" ", "").replace("\n", "").upper()
        self.msg_len = len(self.message)
        # get chi
        self.get_chi()
        # get mu
        self.get_mu()
        # get psi
        self.get_psi()
        # get result
        self.get_result()

    def get_chi(self):
        pos = int(self.chi)
        self.chi_record = []
        for i in range(self.msg_len):
            if pos > len(chi_str):
                pos = 1
            self.chi_record.append(chi_wheel[pos - 1])
            pos += 1

    def get_mu(self):
        pos = int(self.mu)
        self.mu_record = []
        for i in range(self.msg_len):
            if pos > len(mu_str):
                pos = 1
            self.mu_record.append(mu_wheel[pos - 1])
            pos += 1

    def get_psi(self):
        pos = int(self.psi)
        self.psi_record = [psi_wheel[pos - 1]]
        for i in range(1, self.msg_len):
            if self.mu_record[i - 1] == "1":
                pos += 1
            if pos > len(psi_str):
                pos = 1
            self.psi_record.append(psi_wheel[pos - 1])

    def get_result(self):
        xor1 = [int(baudot_table[x], 2) ^ int(y, 2)
                for x, y in zip(self.message, self.chi_record)]
        xor2 = [x ^ int(y, 2)
                for x, y in zip(xor1, self.psi_record)]
        self.result = "".join([baudot_reverse[i] for i in xor2])

    def lorenz_help(self):
        print("Usage:")
        print("echo [MESSAGE] | [./hw04-encrypt|./hw04-decrypt] chi mu psi")

if __name__ == "__main__":
    lz = Lorenz()
    print(lz.result)
