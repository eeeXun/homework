import unittest
from temperature import *

class TestTemp(unittest.TestCase):
    def test_C2F_freezing_point(self):
        self.assertEqual(C2F(0),32,'Should be 32')
    def test_C2F_melting_point(self):
        self.assertEqual(C2F(100),212,'Should be 212')
    def test_F2C_freezing_point(self):
        self.assertEqual(F2C(32),0,'Should be 0')
    def test_F2C_melting_point(self):
        self.assertEqual(F2C(212),100,'Should be 100')

if __name__ == '__main__':
    unittest.main()
