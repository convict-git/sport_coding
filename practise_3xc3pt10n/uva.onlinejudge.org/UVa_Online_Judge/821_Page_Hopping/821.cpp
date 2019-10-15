#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;

const int N = (int)1e2 + 10;
const int infi = (int)1e9;
int W[N][N];
int has[N];

void FloydWarshall() {
   for (int k = 0; k < N; ++k)
      for (int i = 0; i < N; ++i)
         for (int j = 0; j < N; ++j)
            if (W[i][k] < infi && W[k][j] < infi) // to protect overflow
               W[i][j] = min (W[i][j], W[i][k] + W[k][j]);
}

void solve() {
   int u, v, it = 0;
   while (cin >> u >> v, u || v) {
      --u, --v;
      ++it;
      for (int i = 0; i < N; ++i) {
         has[i] = 0;
         for (int j = 0; j < N; ++j)
            W[i][j] = (i == j ? 0 : infi);
      }

      has[u] = has[v] = W[u][v] = 1;
      while (cin >> u >> v, u || v) {
         --u, --v;
         has[u] = has[v] = W[u][v] = 1;
      }

      FloydWarshall();

      int avg = 0, cnt = 0;
      for (int i = 0; i < N; ++i) {
         for (int j = 0; j < N; ++j) {
            if (i == j) continue;
            if (has[i] && has[j]) {
               avg += W[i][j], ++cnt;
            }
         }
      }

      float ans = (float)avg/(float)cnt;
      cout << "Case " << it << ": average length between pages = " << fixed << setprecision(3) << ans << " clicks\n";
   }
}

signed main() {
   solve();

	return EXIT_SUCCESS;
}

