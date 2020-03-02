#include <stdio.h>

long long fib_linear (int n) {
  long long a = 1, b = 1;
  for (int i = 3; i <= n; ++i) {
    long long temp = b;
    b = a + b;
    a = temp;
  }
  return b;

}

int main() {
  printf("Fib of %i is %lld\n", 45, fib_linear(45));
  return 0;
}
