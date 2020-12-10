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
   vector <vector<int>> g;
   g.assign(n, vector <int> ());

   for (int e = 0, u, v; e < m; ++e) {
      cin >> u >> v;
      --u, --v;
      g[u].push_back(v);
   }

   int cyc_idx = -1;
   vector <int> color(n); // initially all white, 0 white 1 gray 2 black
   function <void(int, pair <int, int>)> dfs = [&] (int u, pair <int, int> ban)  {
      color[u] = 1; // color gray
      for (int v : g[u]) {
         if (ban == make_pair(u, v) || color[v] == 2) {
            continue;
         }
         else if (color[v] == 0) {
            dfs (v, ban);
         }
         else { // color[v] == gray, cycle found
            cyc_idx = v;
         }
      }
      color[u] = 2; // color black
   };
   for (int u = 0; u < n; ++u) {
      if (color[u] == 0) {
         dfs(u, {-1, -1}); // no ban
      }
   }
   if (cyc_idx == -1) {
      cout << "YES\n";
   }
   else {
      int rep = cyc_idx;
      vector <pair <int, int>> cyc_edges;
      color.assign(n, 0);
      vector <int> pi(n, -1);
      bool found = false;
      function <void(int)> get_cycle = [&] (int u){
         color[u] = 1;
         for (int v : g[u]) {
            if (found) return;
            if (!color[v]) {
               pi[v] = u;
               get_cycle(v);
            }
            if (v == rep) {
               pi[v] = u;
               found = true;
               return;
            }
         }
      };
      get_cycle(rep);
      int v = rep, u = pi[v];
      cyc_edges.push_back(make_pair(u, v));
      while (u != rep) {
         int tmp = pi[u];
         v = u;
         u = tmp;
         cyc_edges.push_back(make_pair(u, v));
      }
      debug(cyc_edges);

      for (auto e : cyc_edges) {
         cyc_idx = -1;
         color.assign(n, 0);
         for (int i = 0; i < n; ++i) {
            if (!color[i]) dfs(i, e);
         }
         debug("ban", e, cyc_idx);
         if (cyc_idx == -1) {
            cout << "YES\n";
            return;
         }
      }
      cout << "NO\n";
   }
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
