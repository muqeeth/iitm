from pylab import *
from numpy import *
def f(x):
    return 1.0/(1+x*x)
h = 0.5
x = arange(1.0,5.0,h)
y = f(x)
I=[0]
for i,v in enumerate(y):
    if(i!=0):
        I.append(I[i-1]+0.5*h*y[i]+0.5*h*y[i-1])

I = asarray(I)        
print I