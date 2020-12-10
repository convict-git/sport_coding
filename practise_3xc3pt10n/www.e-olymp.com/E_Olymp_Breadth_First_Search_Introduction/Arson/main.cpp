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
   int n, m;
   cin >> n >> m;
   vector <vector <int>> g;
   g.assign(n, vector <int> ());
   for (int e = 0, u, v; e < m; ++e) {
      cin >> u >> v;
      --u, --v;
      g[u].push_back(v);
      g[v].push_back(u);
   }
   int k;
   cin >> k;
   vector <int> fires(k);
   for (int i = 0; i < k; ++i) {
      cin >> fires[i];
      --fires[i];
   }
   const int inf = (int)1e9;
   vector <int> dist(n, inf);
   vector <int> vis(n, false);
   queue <int> q;
   for (int f : fires) {
      dist[f] = 0;
      q.push(f);
   }
   pair <int, int> res = {0, -fires[0]};
   while (!q.empty()) {
      int u = q.front();
      res = max(res, make_pair(dist[u], -u));
      q.pop();
      if (vis[u]) continue;
      vis[u] = true;
      for (int v : g[u]) {
         if (!vis[v] && dist[v] > dist[u] + 1) {
            dist[v] = dist[u] + 1;
            q.push(v);
         }
      }
   }
   cout << res.first << '\n';
   cout << -res.second + 1 << '\n';
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
