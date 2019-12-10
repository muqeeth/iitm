from pylab import *
import matplotlib.pyplot as plt
from numpy import *
def f(x):
    return 1.0/(1+x*x)

def integral(y,h):
    return h*(cumsum(y) - 0.5*(y+y[0]))

def indices(x,y):
    indices = []
    x = x.tolist()
    y = y.tolist()
    for i in x:
        p = y.index(i)
        indices.append(p)
    indices  = asarray(indices)
    return indices

I_list = []
h_list = []
est_error_list = []
actual_error_list = []
h = 0.1
x = arange(0,1+h,h)
y = f(x)
I_list.append(integral(y,h))
count = 1
while True:
    h = h/2
    h_list.append(h)
    x = arange(0,1+h,h)
    y = f(x)
    I_now = integral(y,h)
    I_list.append(I_now)
    x_prev = arange(0,1+h,2*h)
    indices_list = indices(x_prev,x)
    I_prev = I_list[count-1]
    I_prev = asarray(I_prev)
    I_now  = asarray(I_now)
    error = abs(I_now[indices_list]-I_prev)
    error = max(error)
    est_error_list.append(error)
    actual_error = abs(arctan(x_prev)-I_prev)
    actual_error = max(actual_error)
    actual_error_list.append(actual_error)
    count+=1
    if(error<10**(-8)):
        break

print est_error_list
print actual_error_list
# print count
print h_list
plt.ylabel('Error')
plt.xlabel('h')
plt.loglog(h_list,actual_error_list,'ro')
plt.loglog(h_list,est_error_list,'g+')
plt.legend(['Exact error','Estimated error'])
plt.show()