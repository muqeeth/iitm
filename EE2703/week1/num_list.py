import math
from array import *
alpha = math.pi #get value of PI
lst = []
ls =[]
lst.append(0.2)
for k in range(1,1000):
    n = ((lst[k-1]+alpha)*100) #get value of expression
    lst.append(n - int (n))#append to list
for k in range(0,1000):
    ls.append(round(lst[k],4))
    print  ls[k]  #print
