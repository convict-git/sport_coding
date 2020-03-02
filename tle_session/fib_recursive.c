#include <stdio.h>

long long fib (int n) {
  if (n == 1 || n == 2) {
    return 1;
  }
  else {
    return fib(n - 1) + fib(n - 2);
  }
}

int main() {
  printf("Fib of %i is %lld\n", 45, fib(45));
  return 0;
}
