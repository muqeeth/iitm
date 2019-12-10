#include "stdio.h"
int main(int argc, char const *argv[]) {
  int n = 1;
  int nold = 1;
  int new;
  printf("1 %d\n",nold ); //prints first two numbers of fibonacci
  printf("2 %d\n",n );
  for(int i = 3;i<11;i++ ){
    new = n + nold;         //to get new number make new number to be sum of current
    nold = n;                // and old number
    n = new;                  //make new number now the current one
    printf("%d %d\n",i,n );
  }
  return 0;
}
