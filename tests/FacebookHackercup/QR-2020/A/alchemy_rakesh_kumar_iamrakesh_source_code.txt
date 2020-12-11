#include <iostream>

using namespace std;

int main() {
  int t;
  scanf("%d", &t);
  for (int h = 0; h < t; ++h) {
    int n, a = 0, b = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      char c;
      scanf(" %c", &c);
      if (c == 'A')
	a++;
      else
	b++;
    }
    printf("Case #%d: ", h + 1);
    if (abs(a - b) != 1) {
      puts("N");
      continue;
    }
    puts("Y");
  }
  return 0;
}
