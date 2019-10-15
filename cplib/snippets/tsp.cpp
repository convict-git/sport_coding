#include <bits/stdc++.h>
using namespace std;

struct tsp {
   using ll = long long;
   static const int N = 17;
   const ll inf = (ll) 1e18;
   ll dp[N][1 << N];
   int par[N][1 << N], start[N][1 << N], wgt[N][N];
   int n;

   ll solve() {
      //    for (int k = 0; k < n; ++k)    //Floyd-Warshall for shortest dist wgts (undirected)
      //       for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
      //          wgt[j][i] = wgt[i][j] = min(wgt[i][j], wgt[i][k] + wgt[k][j]);

      for (int mask = 0; mask < (1 << n); ++mask)
         for (int i = 0; i < n; ++i)
            dp[i][mask] = inf;

      for (int i = 0; i < n; ++i)
         dp[i][1 << i] = 0, par[i][1 << i] = -1, start[i][1 << i] = i;

      for (int mask = 1; mask < (1 << n); ++mask) {
         for (int pos = 0; pos < n; ++pos)
         {
            if (!(mask & (1 << pos))) continue;
            ll mn_val = inf;
            for (int prv = 0; prv < n; ++prv) {
               if (pos == prv || !(mask & (1 << prv)) || !wgt[prv][pos])
                  continue;
               ll guess = dp[prv][mask-(1<<pos)] + wgt[prv][pos];
               if (mn_val > guess) {
                  mn_val = guess;
                  par[pos][mask] = prv;
                  start[pos][mask] = start[prv][mask-(1 << pos)];
               }
            }
            dp[pos][mask] = min(dp[pos][mask], mn_val);
         }
      }

      ll mn_cycle = inf;
      int pos = -1, mask = (1 << n) - 1;
      for (int i = 0; i < n; ++i) {
         ll go = dp[i][mask] + wgt[i][start[i][mask]];
         if (mn_cycle > go) {
            mn_cycle = go;
            pos = i;
         }
      }

      vector <int> cycle;
      while (pos != -1) {
         cycle.push_back(pos);
         int tmp = pos;
         pos = par[pos][mask];
         mask -= (1 << tmp);
      }
      for (int v : cycle) { cerr << v << ' '; } cerr << '\n';

      return mn_cycle;
   }
};
