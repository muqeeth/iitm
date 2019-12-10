#import libraries
from pylab import *
from numpy import *
import mpl_toolkits.mplot3d.axes3d as p3
import matplotlib.pyplot as plt

#parameters 
Nx=25# size along x
Ny=25# size along y
radius=8# radius of central lead
Niter=1500 # number of iterations to perform

#allocate potential array
phi = zeros((Ny,Nx))

#define x and y coordinates
x = linspace(-0.5,0.5,Nx)
y = linspace(-0.5,0.5,Ny)

#get coordinates where voltage is 1
Y,X = meshgrid(y,x)
ii = where(X*X +Y*Y <= 0.35*0.35)
#set their value to 1
phi[ii] = 1.0

#plot the contour
plt.scatter(Y,X,(phi==1),color='r')
plt.title('points where voltage=1')
plt.grid()
plt.show()


#update potential
count = 0
errors = zeros(Niter)
while(count < Niter):
    phiold = phi.copy()
    phi[1:-1,1:-1] = 0.25*(phiold[1:-1,0:-2]+phiold[1:-1,2:]+phiold[0:-2,1:-1]+phiold[2:,1:-1]) 
    phi[1:-1,0] = phi[1:-1,1]
    phi[1:-1,-1] = phi[1:-1,-2]
    phi[-1,:] = phi [-2,:]
    phi[ii] = 1.0
    errors[count] = (abs(phi-phiold)).max()
    count+=1

#surface plot of voltage
fig1 = figure(1)
ax = p3.Axes3D(fig1)
title('the 3-D surface plot of the potential')
surf=ax.plot_surface(X,Y,phi.T,rstride=1,cstride=1,cmap=cm.jet)
xlabel('X')
ylabel('Y')
ax.set_zlabel('potential')
show()

#iteration vector
x0 = linspace(1,Niter,Niter)
#fit1
P = zeros((Niter,2))
P[:,0] = 1
P[:,1] = x0
q = log(errors)
A,B = lstsq(P,q)[0]
A = exp(A)
y1 = A*exp(B*x0)
#fit2
P = zeros((Niter-500,2))
P[:,0] = 1
P[:,1] = x0[500:]
q = log(errors[500:])
A,B = lstsq(P,q)[0]
A = exp(A)
y2 = A*exp(B*x0)
#plot both models
plt.xlim(-50,1550)
plt.semilogy(x0[::50],errors[::50],'bo')
plt.semilogy(x0[::50],y1[::50],'r^')
plt.semilogy(x0[500::50],y2[500::50],'g--')
plt.legend(['errors','fit A','fit B which is after 500th iteration'],loc="best")
plt.grid()
plt.xlabel('number of iterations')
plt.ylabel('error')
plt.show()

#contour plot
contourf(phi)
title('contour plot of potential')
show()

#quiver plot
Jx = zeros((Ny,Nx))
Jy = zeros((Ny,Nx)) 
Jy[1:-1,1:-1] = 0.5*(phi[0:-2,1:-1]-phi[2:,1:-1]) 
Jx[1:-1,1:-1] = 0.5*(phi[1:-1,0:-2]-phi[1:-1,2:]) 
plt.plot(ii[1],ii[0],'ro')
plt.quiver(Jx[:,:],Jy[:,:])
plt.title('The vector plot of current flow')
plt.show()