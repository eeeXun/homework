def GCD(a,b):
    if b==0:
        return a
    else:
        return GCD(b,a%b)

class Rational:
    def __init__(self,a,b):
        self.numerator=a
        self.denominator=b
        
    def reduce(self):
        gcd=GCD(abs(self.numerator),abs(self.denominator))
        print(gcd)
        self.numerator//=gcd
        self.denominator//=gcd
            
    def add(self,k):
        self.numerator=self.numerator * k.denominator + k.numerator * self.denominator
        self.denominator*=k.denominator
        return self
    
    def __str__(self):
        return '%s / %s'%(self.numerator,self.denominator)

def main():
    a = Rational(24, 36)
    print(a)
    a.reduce()
    print(a)
    b = Rational(2, 3)
    c = a.add(b)
    c.reduce()
    print(c)

main()