n = 1
nold = 1
print 1,nold  #prints first two numbers of fibonacci
print 2,n
for k in range(3,11):   #to print first 10 fibonacci
    new = n + nold      #new number is sum of current and old number
    nold = n            #make current one to be nold
    n = new             #make new number to be current
    print k,new
