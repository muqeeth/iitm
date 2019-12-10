#import required packages
from pylab import *
import matplotlib.pyplot as plt
from numpy import *
import scipy.special as sp
#define bessel function
def jv(x):
    return sp.jv(1,x)

#define calcnu function
def calcnu(x,x0,eps,model):
    indices = where(x>=x0)
    #take from x0 to x
    x = x[indices]
    #get bessel function values in q matrix
    q = jv(x)+ eps*randn(size(x))
    #define matrix P 
    P = zeros((len(x),2))
    if(model == 'A'):
        P[:,0] = cos(x)
        P[:,1] = sin(x)
        A,B=lstsq(P,q)[0]
        phi = arccos(A/sqrt(A*A + B*B))
        nu = 2*(phi-pi/4)/pi
        return nu
    if(model == 'B'):
        P[:,0] = cos(x)/sqrt(x)
        P[:,1] = sin(x)/sqrt(x)
        A,B=lstsq(P,q)[0]
        phi = arccos(A/sqrt(A*A + B*B))
        nu = 2*(phi-pi/4)/pi
        return nu    
   
#define vector x using linspace
n = 41 #number of observations
x = linspace(0,20,n)
#for n=41 x0 ranges from 0.5 to 18 in steps of 0.5
# x0_range = linspace(20.0/(n-1),20-4*(20.0/(n-1)),n-5)
x0_range = linspace(0.5,18,36)

nu_listA =[]
nu_listB =[]
nu_listnoiseB = []
for x0 in x0_range:
    nu_A = calcnu(x,x0,0,'A')
    nu_B = calcnu(x,x0,0,'B')
    nu_noiseB = calcnu(x,x0,0.1,'B')
    nu_listA.append(nu_A)
    nu_listB.append(nu_B)
    nu_listnoiseB.append(nu_noiseB)

plt.xlabel('$x_0$',fontsize = 18)
plt.ylabel(r'$\nu$',fontsize = 18)
plt.plot(x0_range,nu_listA,'go', markersize=5)
plt.plot(x0_range,nu_listB,'bo', markersize=5)
plt.plot(x0_range,nu_listnoiseB,'ro', markersize=5)
plt.legend(['$\epsilon$=0,model A','$\epsilon$=0,model B','$\epsilon$=0.01,model B'],loc ='lower right')
plt.grid(linestyle='dotted')
plt.show()


