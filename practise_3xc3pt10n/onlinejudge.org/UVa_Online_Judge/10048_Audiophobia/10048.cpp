#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = (int)1e2 + 10;
const int infi = (int)1e9;
int dp[N][N];
int n, m, q;
vector < vector <pii> > Adj;

void modFloydWarshall() {
   for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            dp[i][j] = dp[j][i] = min(dp[i][j], max(dp[i][k], dp[k][j]));
}

void read() {
   int it = 0;
   while (cin >> n >> m >> q, n || m || q) {
      if (it) cout << '\n';
      ++it;
      Adj.assign(n, vector <pii>());
      int c1, c2, d;

      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            dp[i][j] = infi;

      for (int i = 0; i < m; ++i) {
         cin >> c1 >> c2 >> d;
         --c1, --c2;
         Adj[c1].push_back(pii(c2, d));
         Adj[c2].push_back(pii(c1, d));
         dp[c1][c2] = dp[c2][c1] = d;
      }

      cout << "Case #" << it << '\n';
      modFloydWarshall();
      while (q--) {
         cin >> c1 >> c2;
         --c1, --c2;
         if (dp[c1][c2] == infi)
            cout << "no path\n";
         else cout << dp[c1][c2] << '\n';
      }
   }
}

signed main() {
   IOS; PREC;
   read();

	return EXIT_SUCCESS;
}

