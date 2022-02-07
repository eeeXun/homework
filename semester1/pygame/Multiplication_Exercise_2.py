# -*- coding: utf-8 -*-
"""
Created on Tue Sep 24 17:54:13 2019

@author: User
"""

import random

fail=0
for i in range(10):
    m1=random.randint(0,99)
    m2=random.randint(0,99)
    print(m1,'*',m2,'=')
    answer=input()
    if answer!=str(m1*m2):
        print('Wrong! ',m1,'*',m2,'=',m1*m2)
        fail=fail+1
print('You made ',fail,' mistakes today.')