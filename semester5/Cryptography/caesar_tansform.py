table_orig = [chr(i) for i in range(ord("A"), ord("Z") + 1)]

def process_key(s):
    value = []
    for i in s:
        if i not in value:
            value.append(i)
    return value

def make_table(key):
    table = [chr(i) for i in range(ord("A"), ord("Z") + 1)]
    for i in key:
        table.remove(i)
    for i in range(len(key)):
        table.insert(i, key[i])
    return table

def main():
    key_orig = input("Key: ")
    msg = input("Message: ")
    key_after = process_key(key_orig.upper())
    table_after = make_table(key_after)
    ans = ""
    for i in msg:
        ans += table_orig[table_after.index(i)]
    print(ans)

if __name__ == "__main__":
    main()
