#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;
const int N = 55;
const int infi = (int)1e9;

int n, q;
int d[N][N];

void floydWarshall() {
   for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
}

void solve(int tc) {
   floydWarshall();
   cin >> q;

   int u, v;
   int totalDist = 0;
   while (q--) {
      cin >> u >> v;
      --u, --v;
      totalDist += d[u][v];
   }
   cout << "Case #" << tc << ": " << totalDist << '\n';
}

void read() {
   cin >> n;
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         cin >> d[i][j];
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   for (int i = 1; i <= tc; ++i) {
      read();
      solve(i);
   }

	return EXIT_SUCCESS;
}

