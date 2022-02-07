# -*- coding: utf-8 -*-
"""
Created on Tue Sep 24 17:44:32 2019

@author: User
"""

import random

m1=random.randint(0,99)
m2=random.randint(0,99)

print(m1,'*',m2,'=')
answer=input()
if answer==str(m1*m2):
    print('Right!')
else:
    print('Wrong! ',m1,'*',m2,'=',m1*m2)