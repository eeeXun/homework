#!/usr/bin/python3
import sys

alpha = [chr(i) for i in range(ord("A"), ord("Z") + 1)]
alpha.remove("J") # J is I
table = [[] for i in range(5)]

def cipher_help():
    print("Usage:")
    print("echo [MESSAGE] | [./hw03-encrypt|./hw03-decrypt] KEY")

def process_key(key):
    result = ""
    for i in key:
        if i == "J" and "I" not in result:
            result += "I"
        elif i not in result:
            result += i
    return result

def process_message(message):
    times = 0
    result = ""
    while True:
        if times >= len(message):
            break
        elif times == len(message) - 1:
            result += message[times]
            result += "X"
            break
        elif message[times] != message[times + 1]:
            result += message[times:times + 2]
            times += 2
        elif message[times] == message[times + 1]:
            result += message[times]
            result += "X"
            times += 1
    return result

def build_table(key):
    for i in range(len(key)):
        table[i // 5].append(key[i])
        alpha.remove(key[i])
    for i in range(len(alpha)):
        table[(i + len(key)) // 5].append(alpha[i])

def find_index(s):
    """
    return row, column in table
    """
    for i in range(5):
        if s == "J" and "I" in table[i]:
            return i, table[i].index("I")
        elif s in table[i]:
            return i, table[i].index(s)

def process_result(message, shift):
    """
    shift == 1 for encrypt, shift == -1 for decrypt
    """
    if shift == 1:
        message = process_message(message)
    # run result
    result = ""
    for i in range(len(message) // 2):
        row_1, col_1 = find_index(message[i * 2])
        row_2, col_2 = find_index(message[i * 2 + 1])
        if row_1 == row_2:
            result += table[row_1][(col_1 + shift) % 5]
            result += table[row_2][(col_2 + shift) % 5]
        elif col_1 == col_2:
            result += table[(row_1 + shift) % 5][col_1]
            result += table[(row_2 + shift) % 5][col_2]
        else:
            result += table[row_1][col_2]
            result += table[row_2][col_1]
    return result

def main():
    mode = sys.argv[0]
    if "hw03-encrypt" not in mode and "hw03-decrypt" not in mode:
        cipher_help()
        exit()
    key = sys.argv[1].upper().replace(" ", "")
    message = ""
    for line in sys.stdin:
        message += line.replace(" ", "").replace("\n", "").upper()
    key = process_key(key)
    build_table(key)
    # process result
    if "hw03-encrypt" in mode:
        result = process_result(message, 1)
    elif "hw03-decrypt" in mode:
        result = process_result(message, -1)
    print(result)

if __name__ == "__main__":
    main()
