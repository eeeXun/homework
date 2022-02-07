#!/usr/bin/python3
import sys
import argparse

def cipher_help():
    print("Usage:")
    print("echo [MESSAGE] | [./hw06-encrypt|./hw06-decrypt] key [-c]")

class Rail:
    def dataInit(self, key: int, msg: str):
        self.rows = key
        self.msg = msg
        self.msg_len = len(msg)
        self.cross = (key - 1) * 2
        self.result = ""
        self.tmp_result = ["" for i in range(key)]

    def encrypt(self, key: int, msg: str):
        self.dataInit(key, msg)
        tmp_pos = 0
        tmp_shift = 1
        for i in range(self.msg_len):
            if tmp_pos > self.rows - 1:
                tmp_pos = self.rows - 2
                tmp_shift = -1
            elif tmp_pos < 0:
                tmp_pos = 1
                tmp_shift = 1
            self.tmp_result[tmp_pos] += self.msg[i]
            tmp_pos += tmp_shift
        ########################################################################
        # for i in range(self.rows):
        #     tmp_pos = i
        #     tmp_cross = self.cross - 2 * i
        #     at_peak = (i == 0) or (i == self.rows - 1)
        #     while True:
        #         if self.outRange(tmp_pos):
        #             break
        #         else:
        #             self.tmp_result += self.msg[tmp_pos]
        #             if not at_peak:
        #                 if not self.outRange(tmp_pos + tmp_cross):
        #                     self.tmp_result += self.msg[tmp_pos + tmp_cross]
        #             tmp_pos += self.cross
        ########################################################################
        # extract
        self.result = "".join(self.tmp_result)
        self.print_result()

    def decrypt(self, key: int, msg: str):
        self.dataInit(key, msg)
        real_pos = 0
        for i in range(self.rows):
            tmp_pos = i
            tmp_cross = self.cross - 2 * i
            at_peak = (i == 0) or (i == self.rows - 1)
            while True:
                if self.outRange(tmp_pos):
                    break
                else:
                    self.tmp_result[i] += self.msg[real_pos]
                    if not at_peak:
                        if not self.outRange(tmp_pos + tmp_cross):
                            real_pos += 1
                            self.tmp_result[i] += self.msg[real_pos]
                    tmp_pos += self.cross
                    real_pos += 1
        # extract
        tmp_row = 0
        tmp_shift = 1
        for i in range(self.msg_len):
            if tmp_row > self.rows - 1:
                tmp_row = self.rows - 2
                tmp_shift = -1
            elif tmp_row < 0:
                tmp_row = 1
                tmp_shift = 1
            self.result += self.tmp_result[tmp_row][0]
            self.tmp_result[tmp_row] = self.tmp_result[tmp_row][1:]
            tmp_row += tmp_shift
        self.print_result()

    def outRange(self, pos: int):
        if pos >= self.msg_len:
            return True
        else:
            return False

    def print_result(self):
        print(self.result)

def main():
    mode = sys.argv[0]
    if "hw06-encrypt" not in mode and "hw06-decrypt" not in mode:
        cipher_help()
        exit(1)
    parser = argparse.ArgumentParser(description="Rail Fence Cipher")
    parser.add_argument("key", help="Number of rows (rails)")
    parser.add_argument("-c", "--comma", help="display spaces as commas", action="store_true")
    args = parser.parse_args()
    key = int(args.key)
    # msg
    msg = ""
    for line in sys.stdin:
        msg += line.replace("\n", " ").upper()[:-1]
    # encrypt / decrypt
    cipher = Rail()
    if "hw06-encrypt" in mode:
        if args.comma:
            msg = msg.replace(" ", ",")
        cipher.encrypt(key, msg)
    elif "hw06-decrypt" in mode:
        if args.comma:
            msg = msg.replace(",", " ")
        cipher.decrypt(key, msg)

if __name__ == "__main__":
    main()
