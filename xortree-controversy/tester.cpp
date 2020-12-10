// Hack it and have it ;) //
/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows!* * * * * * */
#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#define xored(x) (((1ll << 31) - 1) ^ x)

void preproc() {
}

void solve() {
   int n, k;
   cin >> n >> k;

   vector <int> ar(n);
   vector <vector <int>> g(n, vector <int> ());
   vector <bool> vis(n);
   vector <vector <long long>> dp(n, vector <long long> (k + 1, -1));

   // take the input node values and the input graph
   for (int i = 0; i < n; ++i) cin >> ar[i];
   for (int i = 0, u, v; i < n - 1; ++i) {
      cin >> u >> v;
      g[u].push_back(v), g[v].push_back(u);
   }

   // root the whole tree at 0 (it makes it easier to work on)
   function <void(int, int)> root_at = [&] (int u, int pr) {
      for (int i = 0; i < (int)g[u].size(); ++i)
         if (g[u][i] == pr) {
            g[u].erase(g[u].begin() + i);
            break;
         }
      for (int v : g[u])
         root_at(v, u);
   };
   root_at(0, -1);

   // remember the tree is rooted at 0, so subtree definition depends accordingly
   // dp[u][nop] := largest possible sum we can get by applying exactly nop operations
   //				on u's subtree
   // dfs -> total number of states = O(n * k),
   // and each state (u, nop), it takes O(#childs(u) * (nop ^ 2)) time to compute
   // hence O(n * (k^3)) solution

   function <void(int, int)> dfs = [&] (int u, int nop) -> void {
      dp[u][nop] = (nop & 1 ? xored(ar[u]) : ar[u]);

      for (int v : g[u])
         for (int x = 0; x <= nop; ++x)
            if (dp[v][x] == -1) dfs(v, x);

      int sz = (int)g[u].size();
      // prefix dp
      vector <vector <long long>> pref(nop + 1, vector <long long> (2));
      for (int i = 0; i < sz; ++i) {
         int v = g[u][i];
         for (int x = 0; x <= nop; ++x) { //(prefix + current nodes)'s contrubution is x
            pref[x][i & 1] = dp[v][x] + pref[0][!(i & 1)];
            for (int y = 0; i && y <= x; ++y) // current node's contribution is y
               pref[x][i & 1] = max(pref[x][i & 1], pref[x - y][!(i & 1)] + dp[v][y]);
         }
      }
      dp[u][nop] += pref[nop][!(sz & 1)];
   };
   dfs(0, k);

   // answer is stored in dp[0][k]
   cout << dp[0][k] << "\n";
}

signed main() {
   IOS; PREC;
   preproc();

   int tc = 1;
   // cin >> tc;
   for (int Tt = 1; Tt <= tc; ++Tt) {
      // cout << "Case #" << Tt << ": ";
      solve();
   }
   return EXIT_SUCCESS;
}
