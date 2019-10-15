#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;
const int N = 305;

int n, q;
int W[N][N];

void floydWarshall() {
   for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            W[i][j] = W[j][i] = min(W[i][j], W[i][k] + W[k][j]);
}

void solve() {
   floydWarshall();
   cin >> q;
   int u, v, c;
   while (q--) {
      cin >> u >> v >> c;
      --u, --v;

      long long totalSD = 0;
      for (int i = 0; i < n; ++i) {
         for (int j = i + 1; j < n; ++j) {
            W[i][j] = W[j][i] = min(W[i][j], min(W[i][u] + W[v][j] + c, W[i][v] + W[u][j] + c));
            totalSD += 1ll*W[i][j];
         }
      }
      cout << totalSD << ' ';
   }
   cout << '\n';
}

void read() {
   cin >> n;
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         cin >> W[i][j];
}

signed main() {
   IOS; PREC;
   read();
   solve();

	return EXIT_SUCCESS;
}
