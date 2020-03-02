#include <stdio.h>

typedef struct FibStruct {
  long long a, b;
} FibStruct;

FibStruct g (FibStruct f) {
  FibStruct F = {f.b, f.b + f.a};
  return F;
}

FibStruct expo (FibStruct f, int n) {
  if (n == 0) {
    return f;
  }
  else if (n % 2 == 1) {
    return g(expo(f, n - 1));
  }
  else {
    return expo(expo(f, n / 2), n / 2);
  }
}

int main() {
  FibStruct init = {0, 1};
  printf("Fib of %i is %lld\n", (int)1e10, expo(init, (int)1e10).a);
  return 0;
}


