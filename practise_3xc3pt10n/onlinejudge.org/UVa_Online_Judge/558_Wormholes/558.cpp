#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    "[ " << #x << " : " << x << " ]"
#define x        first
#define y        second
using namespace std;

const int N = 1004;
const int infi = (int)1e9;

int n, m;
int W[N][N];

bool floydWarshall() {
   for (int k = 0; k < n; ++k) {
      for (int i = 0; i < n; ++i) {
         for (int j = 0; j < n; ++j) {
            if (W[i][k] < infi && W[k][j] < infi) {
               W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
               if (W[i][i] < 0) return false;
            }
         }
      }
   }
   return true;
}

void solve() {
   cout << (!floydWarshall() ? "possible\n" : "not possible\n");
}

void read() {
   cin >> n >> m;
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         W[i][j] = infi;

   int u, v, w;
   for (int e = 0; e < m; ++e) {
      cin >> u >> v >> w;
      W[u][v] = w;
   }
}

signed main() {
   int tc;
   cin >> tc;
   while (tc--) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

