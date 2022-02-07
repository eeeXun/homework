#!/usr/bin/python3
import sys

def opt_help():
    print("Usage:")
    print("echo [MESSAGE] | [./hw12-encrypt|./hw12-decrypt] (filename of key)")

class OPT:
    table = {
            "A": "1", "E": "2", "I": "3", "N": "4", "O": "5", "T": "6",
            "B": "70", "C": "71", "D": "72", "F": "73", "G": "74", "H": "75", "J": "76", "K": "77", "L": "78", "M": "79",
            "P": "80", "Q": "81", "R": "82", "S": "83", "U": "84", "V": "85", "W": "86", "X": "87", "Y": "88", "Z": "89",
            "1": "90", "2": "90", "3": "90", "4": "90", "5": "90", "6": "90", "7": "90", "8": "90", "9": "90", "0": "90", # FIG
            ".": "91", ":": "92", "'": "93", "(": "94", ")": "94", "+": "95", "-": "96", "=": "97", "?": "98", " ": "99",
            }

    def __init__(self):
        self.result = ""

    def encrypt(self, key, message):
        msg_digit = self.char2digit(message)
        msg_align = self.align(key, msg_digit)
        self.add_mod(msg_align, key)
        print(self.result)

    def decrypt(self, key, message):
        self.sub_mod(message, key)
        plaintxt = self.digit2char(self.result)
        print(plaintxt)

    def char2digit(self, s):
        tmp = ""
        fig_on = False
        for i in s:
            table_digit = int(self.table[i])
            if not fig_on and table_digit == 90:
                fig_on = True
                tmp += "90" + i + i + i
            elif fig_on and table_digit == 90:
                tmp += i + i + i
            elif fig_on and 91 <= table_digit <= 97:
                tmp += self.table[i]
            elif fig_on and self.table[i] != 90 and not(91 <= table_digit <= 97):
                fig_on = False
                tmp += "90" + self.table[i]
            else:
                tmp += self.table[i]
        if fig_on:
            tmp += "90"
        return tmp

    def digit2char(self, s):
        tmp = ""
        keep = False
        keep_msg = ""
        fig_on = False
        for i in s:
            if fig_on:
                keep_msg += i
                if len(keep_msg) == 2 and 91 <= int(keep_msg) <= 97:
                    tmp += self.find_key_by_value(keep_msg)
                    keep_msg = ""
                elif len(keep_msg) == 2 and keep_msg == "90":
                    fig_on = False
                    keep_msg = ""
                elif len(keep_msg) == 3 and keep_msg[0] == keep_msg[1] == keep_msg[2]:
                    tmp += keep_msg[0]
                    keep_msg = ""
            elif keep:
                keep_msg += i
                if not fig_on and keep_msg == "90":
                    fig_on = True
                    keep = False
                    keep_msg = ""
                else:
                    tmp += self.find_key_by_value(keep_msg)
                    keep = False
                    keep_msg = ""
            elif 0 <= int(i) <= 6:
                tmp += self.find_key_by_value(i)
            else:
                keep = True
                keep_msg += i
        return tmp

    def align(self, key, msg):
        ken_len = len(key)
        msg_len = len(msg)
        if ken_len == msg_len:
            replacement = ""
        elif (ken_len - msg_len) % 2 == 0:
            replacement = "91" * ((ken_len - msg_len) // 2)
        else:
            replacement = "91" * ((ken_len - msg_len) // 2) + "9"
        return msg + replacement

    def find_key_by_value(self, s):
        return list(self.table.keys())[list(self.table.values()).index(s)]

    def add_mod(self, msg, key):
        for i in range(len(msg)):
            self.result += str((int(msg[i]) + int(key[i])) % 10)

    def sub_mod(self, msg, key):
        for i in range(len(msg)):
            self.result += str((int(msg[i]) - int(key[i])) % 10)

def main():
    mode = sys.argv[0]
    if ("hw12-encrypt" not in mode and "hw12-decrypt" not in mode) or len(sys.argv) != 2:
        opt_help()
        exit(1)
    else:
        key_file = sys.argv[1]
        with open(key_file, "r") as f:
            key = f.read().replace("\n", "").upper()
    message = input().upper()
    opt = OPT()
    if "hw12-encrypt" in mode:
        opt.encrypt(key, message)
    elif "hw12-decrypt" in mode:
        opt.decrypt(key, message)

if __name__ == "__main__":
    main()
