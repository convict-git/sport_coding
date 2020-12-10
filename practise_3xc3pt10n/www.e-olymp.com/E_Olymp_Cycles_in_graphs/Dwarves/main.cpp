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
   int m;
   cin >> m;
   map <string, int> mp;
   vector <pair<int, int>> edges;
   int n = 0;
   auto idx = [&] (const string &s) { // gives idx for string
      if (mp.find(s) == mp.end())
         mp[s] = n++;
      return mp[s];
   };
   for (int i = 0; i < m; ++i) { // take m edges
      string u, v, sign;
      cin >> u >> sign >> v;
      if (sign == ">")  {
         edges.push_back(make_pair(idx(u), idx(v)));
      }
      else {
         edges.push_back(make_pair(idx(v), idx(u)));
      }
   }
   vector <vector <int>> g;
   g.assign(n, vector <int> ());
   for (auto e : edges) {
      g[e.first].push_back(e.second); // dir edges
   }
   vector <int> color(n); // mark white
   bool ok = true;
   function <void(int)> dfs = [&] (int u) {
      color[u] = 1; // mark grey
      for (int v : g[u]) {
         if (color[v] == 1) { // gray vertex
            ok = false; // cycle found visited already vis
            return;
         }
         if (color[v] == 0)  {
            dfs(v);
         }
      }
      color[u] = 2; // mark black
   };
   for (int i = 0; i < n; ++i) {
      if (color[i] == 0) {
         dfs(i);
      }
   }
   cout << (ok ? "possible\n" : "impossible\n");
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
