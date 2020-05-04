#include <stdio.h>
#include <math.h>

int main() {
  int amt;
  double balance;
  scanf("%i%lf", &amt, &balance);

  if (amt <= balance - 0.5 && amt % 5 == 0) {
    balance = balance - 0.5 - amt;
  }

  printf ("%lf", balance);
  return 0;
}
