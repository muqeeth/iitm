#import packages
from pylab import *
from numpy import *
from matplotlib import *
import sys
#user input using sys.argv
try:
    n = int(sys.argv[1])
    M = int(sys.argv[2])
    nk = int(sys.argv[3])
    u0 = int(sys.argv[4])
    p = float(sys.argv[5])
except:
    n=100 # spatial grid size.
    M=5 # number of electrons injected per turn.
    nk=500 # number of turns to simulate.
    u0=7 # threshold velocity.
    p=0.5 # probability that ionization will occur
Msig=2#standard deviation
#Create vectors to hold the electron information
xx = zeros((n*M))
u = zeros((n*M))
dx = zeros((n*M))
#information from simulation
I = []#Intensity of emitted light
X = []#Electron position
V = []#Electron velocity
#loop begins 
for k in range(1,nk+1):
    ii = where(xx>0)[0]
    dx[ii] = u[ii] + 0.5
    xx[ii] = xx[ii] + dx[ii]
    u[ii] = u[ii] + 1 
    #set position velocity of elec which reach anode
    jj = where(xx>=n)[0]
    u[jj] = 0
    xx[jj] = 0
    dx[jj] =0
    #those elec whose energy>threshold
    kk = where(u>=u0)[0]
    ll = where(rand(len(kk))<=p)[0]
    kl = kk[ll]
    xx[kl]=xx[kl]-dx[kl]
    u[kl]=u[kl]-1
    dt = rand(len(kl))
    dx[kl] = u[kl]*dt + 0.5*dt*dt
    xx[kl] =xx[kl]+dx[kl]
    u[kl]=1-dt
    I.extend(xx[kl].tolist())
    xx[kl]=xx[kl]+0.5*(1-dt)*(1-dt)
    m=int(randn()*Msig+M)
    pp = where(xx>0)[0]
    X.extend(xx[pp].tolist())
    V.extend(u[pp].tolist())
    m1 = where(xx==0)[0]    
    y=m1[0:min(len(m1),m)]
    xx[y]=1
title('Emission Intensity')
xlabel('x')
ylabel('I') 
hist(I,100,normed=1,color='white')
show()
title('Electron density')
xlabel('x')
ylabel('Number of electrons that cross x')
hist(X,100,color='white')
show()
title('Electron phase space')
xlabel('x')
ylabel('v')
plot(X,V,'ro',markersize=4)
show()
population_count=hist(I,100)[0]
bins = hist(I,100)[1]
xpos= 0.5*(bins[0:-1]+bins[1:])
for x in range(len(xpos)):
    print "%f  %d\n" %(xpos[x],population_count[x])
