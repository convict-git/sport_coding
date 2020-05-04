#include<bits/stdc++.h>
using namespace std ;

int main() {
  int t, n ;
  long long x, p ;
  scanf("%d", &t); // input: number of test cases (t)
  while( t-- ) {
    scanf("%d", &n); // input: time in ms (n)
    n-- ;
    x = n % 26 ;
    int k = n/26;
    p = pow(2, k) ; // n/26 equals the number of cycles
    // printing the output after checking if its a bit/nibble/byte
    if(x < 2)
      printf("%lld 0 0\n", p);
    else if( x < 10 )
      printf("0 %lld 0\n", p);
    else
      printf("0 0 %lld\n", p);
  }
  return 0 ;
}




