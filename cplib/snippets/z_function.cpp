#include <bits/stdc++.h>
using namespace std;
const int N = (int)1e6 + 10;
int z[N];

void z_function(const string &st) {
   z[0] = 0;

   // r should be right most, i will always be in range of [l, r]
   for (int i = 1, l = 0, r = -1; i < n; ++i) {
      //calculate initial value of z[i]
      z[i] = (r >= i ? min(z[i - l + 1 - 1], r - i + 1) : 0);

      while (i + z[i] - 1 <= n - 1 && st[i + z[i]] == st[z[i]])
         ++z[i];
      if (r < i + z[i] - 1)
         l = i, r = i + z[i] - 1;
   }
}
