#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;

signed main() {
   int n = 3, m = 4;
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
         cout << m * i + j << ' ';
      }
      cout << '\n';
   }

   return EXIT_SUCCESS;
}

