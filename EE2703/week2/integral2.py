from pylab import *
from numpy import *
def f(x):
    return 1.0/(1+x*x)
h = 0.5
x = arange(1.0,5.0,h)
y = f(x)
I = h*(cumsum(y) - (0.5*(y+y[0])))
print I