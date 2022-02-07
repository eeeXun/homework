#!/usr/bin/python3

class Hellman:
    def __init__(self, g: int, p: int):
        self.g = g
        self.p = p
        self.result = [[] for i in range(p - 1)]
        self.unique = [True for i in range(p - 1)]
        self.enumerate()
        self.show_result()

    def enumerate(self):
        for i in range(1, self.p):
            for j in range(1, self.p):
                tmp = pow(self.g, i * j) % self.p
                if tmp in self.result[i - 1]:
                    self.unique[i - 1] = False
                self.result[i - 1].append(tmp)

    def show_result(self):
        print("  |" + "".join(["{:>2d} ".format(i) for i in range(1, self.p)]))
        print("--+" + "---" * (self.p - 1))
        for i in range(self.p - 1):
            print("{:>2d}|".format(i + 1)
                    + "".join(["{:>2d} ".format(j) for j in self.result[i]])
                    + (" Bad" if not self.unique[i] else ""))

def main():
    ans = input("g, p = ").split(", ")
    if len(ans) != 2:
        raise Exception("Please input '2' numbers, g, p")
    g, p = (int(i) for i in ans)
    Hellman(g, p)

if __name__ == "__main__":
    main()
