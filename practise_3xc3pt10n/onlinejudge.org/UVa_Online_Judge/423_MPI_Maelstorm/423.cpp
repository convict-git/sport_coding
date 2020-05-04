#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;

const long long inf = (long long) 1e18;
int n;
long long W[105][105];

void floydWarshall() {
   for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            if (W[i][k] < inf && W[k][j] < inf)
               W[i][j] = W[j][i] = min(W[i][j], W[i][k] + W[k][j]);
}

void read() {
   while (scanf(" %i", &n) == 1) {
      int w;
      string s;
      for (int i = 0; i < n; ++i)
         W[i][i] = 0;

      for (int i = 1; i <= n - 1; ++i) {
         for (int j = 0; j < i; ++j) {
            if (scanf (" %i", &w) == 1) W[i][j] = W[j][i] = 1ll*w;
            else {
               getchar(); getchar();
               W[i][j] = W[j][i] = inf;
            }
         }
      }
      for (int i = 0; i < n; ++i) {
         for (int j = 0; j < n; ++j) {
            cerr << W[i][j] << " ";
         }
         cerr << '\n';
      }
      floydWarshall();
      long long mx = -inf;
      for (int i = 1; i < n; ++i) {
         mx = max (mx, W[0][i]);
      }
      printf("%lld\n", mx);
   }
}

signed main() {
   read();

	return EXIT_SUCCESS;
}

