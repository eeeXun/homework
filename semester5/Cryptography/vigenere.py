alpha = [chr(i) for i in range(ord("A"), ord("Z") + 1)]
table = {i: ord(i) - ord("A") for i in alpha}
table_lookback = {ord(i) - ord("A"): i for i in alpha}

def process_key(key, text):
    if len(key) > len(text):
        return key
    else:
        for i in range(len(text) - len(key)):
            key += key[i % len(key)]
        return key

def encrypt():
    key = input("key: ").upper()
    message = input("message: ").upper()
    key = process_key(key, message)
    result = ""
    for i in range(len(message)):
        tmp = table[key[i]] + table[message[i]]
        if tmp > table["Z"]:
            result += table_lookback[tmp % 26]
        else:
            result += table_lookback[tmp]
    print(result)


def decrypt():
    key = input("key: ").upper()
    cipher_text = input("cipher_text: ").upper()
    key = process_key(key, cipher_text)
    result = ""
    for i in range(len(cipher_text)):
        tmp = table[cipher_text[i]] - table[key[i]]
        if tmp < 0:
            result += table_lookback[tmp + 26]
        else:
            result += table_lookback[tmp]
    print(result)

def main():
    ans = input("Encript(E) or Decript(D): ")
    if ans.upper() == "E":
        encrypt()
    elif ans.upper() == "D":
        decrypt()

if __name__ == "__main__":
    main()
