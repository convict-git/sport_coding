#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

void preproc() {
}

void solve() {
   int n, k, m;
   cin >> n >> k >> m;
   vector <vector <int>> g;
   g.assign(n, vector <int> ());
   for (int e = 0, u, v; e < m; ++e) {
      cin >> u >> v;
      --u, --v;
      g[u].push_back(v);
      g[v].push_back(u);
   }
   vector <int> vis(n);
   function <int(int)> dfs = [&] (int u) -> int { // dfs gives no. of vert in conn comp
      vis[u] = 1;
      for (int v : g[u]) {
         if (!vis[v]) vis[u] += dfs(v);
      }
      return vis[u];
   };
   vector <bool> knp(k + 1); // knapsack with limit k
   int res = 0;
   knp[0] = 1; // base case
   for (int i = 0; i < n; ++i) {
      if (!vis[i]) {
         int val = dfs(i); // take the value update the knapsack
         for (int l = k; l >= 0; --l) { // fill in reverse order
            if (l + val <= k && knp[l]) {
               knp[l + val] = true;
               res = max(res, l + val);
            }
         }
      }
   }
   cout << res << '\n';
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
