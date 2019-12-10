#include<stdio.h>
#include<math.h>
#define PI (3.141592653589793) //define const PI
int main(int argc, char const *argv[]) {
  double n[1000];
  n[0]=0.2;
  for(int k = 1; k<1000;k++){
    double p;
    p =  ((n[k-1]+PI)*100); //get the value
    n[k] =  p - (int)(p);   // store its fractional part
  }
  for(int k = 0;k<1000;k++){
    //printf("%0.3f\n",n[k]); //print 3 digits after decimal    
    printf("%0.4f\n",n[k]); //print 4 digits after decimal
  }
  return 0;
}
