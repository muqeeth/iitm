from pylab import *
from scipy.integrate import quad
import matplotlib.pyplot as plt
from numpy import *
def func(t):
    return 1.0/(1+t**2)

t=arange(0,5.1,0.1)
l = []
ta =[]
for x in t:
    temp = quad(func,0,x)[0] #get values
   # temp = round(quad(func,0,x)[0],5) # to round off to 5 decimals 
    ta.append( quad(func,0,x)[1]) #get errors
    l.append(temp)

# y = asarray(l)
# y1 = arctan(t)
# plt.title('linear graph of quad func and tan-1(x) vs x ')
# plt.ylabel('arctan')
# plt.xlabel('x')
# plt.plot(t,y,'ro')
# plt.plot(t,y1,'k')
# plt.legend(['quad func','$tan(-1)(x)$'])
# plt.show()


#uncomment below for error
y = asarray(l)
y1 = arctan(t)
tm =abs( y1 - y)
tm = asarray(tm)
plt.title('error in integral semilog graph ')
plt.ylabel('error')
plt.xlabel('x')
plt.semilogy(t,tm,'ro') 
plt.show()
