import unittest

from ex07_prime import isPrime

class TestPrime(unittest.TestCase):

    def test_prime(self):
        for i in [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43,
                  47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97]:
            self.assertEqual(isPrime(i), True)
    def test_notprime(self):
        for i in [4,9,16]:
            self.assertEqual(isPrime(i),False)

if __name__ == '__main__':
    unittest.main()

