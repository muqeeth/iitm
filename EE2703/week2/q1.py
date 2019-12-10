from pylab import *
from numpy import *
def f(x):
    return 1.0/(1+x*x)
x=arange(0,5.1,.1)
y = f(x)
print y