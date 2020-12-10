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
   int n, m, s;
   cin >> n >> m >> s;
   --s;
   vector <vector <int>> g;
   g.assign(n, vector <int> ()); // directed
   for (int e = 0, u, v; e < m; ++e) {
      cin >> u >> v;
      --u, --v;
      g[v].push_back(u);
   }
   const int inf = (int)1e9;
   vector <int> dist(n, inf);
   vector <bool> vis(n, false);
   queue <int> q;
   dist[s] = 0;
   q.push(s);
   int res = 0;
   while (!q.empty()) {
      int u = q.front();
      res = max(res, dist[u]);
      q.pop();
      if (vis[u]) continue;
      for (int v : g[u]) {
         if (!vis[v] && dist[v] > dist[u] + 1) {
            dist[v] = dist[u] + 1;
            q.push(v);
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
