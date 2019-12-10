from pylab import *
import matplotlib.pyplot as plt
from numpy import *
def f(x):
    return 1.0/(1+x*x)
x=arange(0,5.1,.1)
y = f(x)
plt.plot(x,y)
plt.ylabel('y = f(x)')
plt.xlabel('x')
plt.title(' linear graph of f(x) vs x')
plt.legend([r'Plot of $1/(1+x^{2})$'])
plt.show()