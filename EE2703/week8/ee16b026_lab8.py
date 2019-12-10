from sympy import *
import scipy.signal as sp
import pylab as p
s = symbols('s')
def lowpass(R1,R2,C1,C2,G,Vi):
    A=Matrix([[0,0,1.0,-1.0/G],[-1.0/(1.0+s*R2*C2),1.0,0,0],
    [0,-1000.0,1000.0,1.0],[-1.0/R1-1.0/R2-s*C1,1.0/R2,0,s*C1]])
    b=Matrix([0,0,0,-Vi/R1])
    V=A.inv()*b
    return (A,b,V)
def highpass(R1,R2,C1,C2,G,Vi):
    A=Matrix([[0,0,1.0,-1.0/G],[-1.0/(1.0+1.0/(s*R2*C2)),1.0,0,0],
    [0,1000.0,-1000.0,1.0],[-1.0/R1-s*C1-s*C2,s*C2,0,1.0/R1]])
    b=Matrix([0,0,0,-Vi*s*C1])
    V=A.inv()*b
    return (A,b,V)
#for lowpass
A,b,V=lowpass(10000.0,10000.0,1e-9,1e-9,1.586,1.0)
Vo=V[3]
print simplify(Vo)
w=p.logspace(0,8,801)
ss= 1j*w
hf=lambdify(s,Vo,'numpy')
v=hf(ss)
p.loglog(w,abs(v),lw=2)
p.title('Low pass filter')
p.xlabel('$\omega(rad/s)$')
p.ylabel('$Magnitude$')
p.grid(True)
p.show()
#unit step response
H=sp.lti([0.1],[6.31517e-12,8.9455e-7,0.0631517,0])
t,x=sp.impulse(H,None,p.linspace(0,0.0001,1001))
p.title('unit step response of low pass filter')
p.xlabel('t')
p.ylabel('$V_o(t)$')
p.plot(t,x)
p.grid(True)
p.show()

#for sinusoidal input
H=sp.lti([0.1],[6.31517e-12,8.9455e-7,0.0631517])
t=p.linspace(0.0,1e-2,10001)
u=p.sin(2e3*p.pi*t)+p.cos(2e6*p.pi*t)
t,y,svec=sp.lsim(H,u,t)
p.title('response of low pass filter for sinusoidal input')
p.xlabel('t')
p.ylabel('$V_o(t)$')
p.plot(t,y)
p.grid(True)
p.show()

#for highpass
A,b,V=highpass(10000.0,10000.0,1e-9,1e-9,1.586,1.0)
Vo=V[3]
print simplify(Vo)
w=p.logspace(0,8,801)
ss= 1j*w
hf=lambdify(s,Vo,'numpy')
v=hf(ss)
p.loglog(w,abs(v),lw=2)
p.title('High pass filter')
p.xlabel('$\omega(rad/s)$')
p.ylabel('$Magnitude$')
p.grid(True)
p.show()
#unit step response
H=sp.lti([1e-9,0],[6.2951e-10,8.885e-5,6.29517])
t,x=sp.impulse(H,None,p.linspace(0,0.0001,1001))
p.title('unit step response of high pass filter')
p.xlabel('t')
p.ylabel('$V_o(t)$')
p.plot(t,x)
p.grid(True)
p.show()

#for sinusoidal input
H=sp.lti([1e-9,0,0],[6.2951e-10,8.885e-5,6.29517])
t=p.linspace(0,5e-4,1001)
u=p.exp(-1e4*t)*p.cos(2e5*p.pi*t)
t,y,svec=sp.lsim(H,u,t)
p.title('response of high pass filter for damped sinusoidal input')
p.xlabel('t')
p.ylabel('$V_o(t)$')
p.plot(t,y)
p.grid(True)
p.show()