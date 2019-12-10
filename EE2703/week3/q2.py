from pylab import *
import matplotlib.pyplot as plt
from numpy import *
from scipy.integrate import quad
def f(x):
    return exp(x)

def g(x):
    return cos(cos(x))

def u(x,k):
    return f(x)*cos(k*x)

def v(x,k):
    return f(x)*sin(k*x)

a = []
b = []
#get fourier coefficients of exp(x) into a and b lists
a.append((quad(u,0,2*pi,args=(0)))[0]/(2*pi))
for k in range(1,26):
    a.append(quad(u,0,2*pi,args=(k))[0]/pi)
    b.append(quad(v,0,2*pi,args=(k))[0]/pi)

def w(x,k):
    return g(x)*cos(k*x)

def z(x,k):
    return g(x)*sin(k*x)

c = []
d = []
#get fourier coefficients of cos(cos(x)) into  c and d lists
c.append((quad(w,0,2*pi,args=(0)))[0]/(2*pi))
for k in range(1,26):
    c.append(quad(w,0,2*pi,args=(k))[0]/pi)
    d.append(quad(z,0,2*pi,args=(k))[0]/pi)

#To take coefficients in given vector form of integral approach
c1_intg = [0]*(len(a)+len(b))
c1_intg[0] = a[0]
c1_intg[1::2] = a[1:]
c1_intg[2::2] = b# Now c1_intg has exp(x) fourier coefficients

c2_intg = [0]*(len(c)+len(d))
c2_intg[0] = c[0]
c2_intg[1::2] = c[1:]
c2_intg[2::2] = d#Now c2_intg has cos(cos(x)) fourier


#least square approach
x=linspace(0,2*pi,401)
x=x[:-1] # drop last term to have a proper periodic integral
b=f(x)
c=g(x)
# f has been written to take a vector
A=zeros((400,51))
# allocate space for A
A[:,0]=1
# col 1 is all ones
for k in range(1,26):

    A[:,2*k-1]=cos(k*x) # cos(kx) column
    A[:,2*k]=sin(k*x)
# sin(kx) column
#endfor


c1_lsa=lstsq(A,b)[0]#coefficients of exp(x) using leastsquares approach
c1_intg = asarray(c1_intg) 
deviation = max(abs(c1_lsa-c1_intg))#get max deviation
print deviation

c2_lsa=lstsq(A,c)[0]#coefficients using leastsquares approach
c2_intg = asarray(c2_intg)
deviation = max(abs(c2_lsa-c2_intg))#get max deviation
print deviation

#to print coefficients of exp(x) and cos(cos(x)) with both approaches
print c1_intg
print c2_intg
print c1_lsa
print c2_lsa


x1 = arange(0,51,1)#we take 26 a_n and 25 b_n coefficients
#semilog plot of coefficients of exp(x)
plt.title('semilog plot of coefficients of exp(x)')
plt.semilogy(x1,absolute(c1_intg),'ro')
plt.semilogy(x1,absolute(c1_lsa),'go')
plt.xlabel('n')
plt.ylabel('magnitude of coefficients')
plt.legend(['$integral approach$','$leastsquares approach$'],loc='best')
plt.show()
#loglog plot of coefficients of exp(x)
plt.title('loglog plot of coefficients of exp(x)')
plt.loglog(x1,absolute(c1_intg),'ro')
plt.loglog(x1,absolute(c1_lsa),'go')
plt.xlabel('n')
plt.ylabel('magnitude of coefficients')
plt.legend(['$integral approach$','$leastsquares approach$'],loc='best')
plt.show()
#semilog plot of coefficients of cos(cos(x))
plt.title('semilog plot of coefficients of cos(cos(x))')
plt.semilogy(x1,absolute(c2_intg),'ro')
plt.semilogy(x1,absolute(c2_lsa),'go')
plt.xlabel('n')
plt.ylabel('magnitude of coefficients')
plt.legend(['$integral approach$','$leastsquares approach$'],loc='best')
plt.show()
#loglog plot of coefficients of exp(x)
plt.title('loglog plot of coefficients of cos(cos(x))')
plt.loglog(x1,absolute(c2_intg),'ro')
plt.loglog(x1,absolute(c2_lsa),'go')
plt.xlabel('n')
plt.ylabel('magnitude of coefficients')
plt.legend(['$integral approach$','$leastsquares approach$'],loc='best')
plt.show()

#get values of functions by performing matrix multiplication on A and coefficients from least squares
fn_values = dot(A,c1_lsa)
gn_values = dot(A,c2_lsa)

def f1(x):
    return exp(x)

def f2(x):
    return cos(cos(x))

def f3(x):
    l = []
    for i in x:
        if(i<0):
            i = i + 2*pi
        if(i>2*pi):
            i = i - 2*pi
        l.append(i)
    return exp(l)

def f4(x):
    return cos(cos(x))

x=linspace(0,2*pi,401)
x=x[:-1] # drop last term to have a proper periodic integral
x1 = arange(-2*pi,4*pi,0.1)
y1 = f1(x1)
y2 = f2(x1)
y3 = f3(x1)
y4 = f4(x1)
plt.semilogy(x1,y1,'r')
plt.semilogy(x1,y3,'k')
plt.semilogy(x,fn_values,'go')
plt.grid(color='k',linestyle ='-',linewidth = 1)
plt.xlabel('x')
plt.ylabel('$f(x) = e^x$')
plt.legend(['semilog plot of f(x) vs x','expected plot from fourier','plot from leastsquares'],loc='best')
plt.show()

plt.plot(x1,y2,'r')
plt.plot(x1,y4,'k')
plt.plot(x,gn_values,'go')
plt.grid(color='k',linestyle ='-',linewidth = 1)
plt.xlabel('x')
plt.ylabel('$f(x) = cos(cos(x))$')
plt.legend(['linear plot of f(x) vs x','expected plot from fourier','plot from leastsquares'],loc='best')
plt.show()





