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

void preproc()
{
}

void solve()
{
   int N, M;
   cin >> N >> M;
   vector <vector <pair <int, int>>> g;
   g.assign(N, vector <pair <int, int>>());
   int low = INT_MAX, high = INT_MIN;
   for (int e = 0; e < M; ++e) {
      int u, v, w;
      cin >> u >> v >> w;
      low = min(low, w), high = max(high, w);
      --u, --v;
      g[u].push_back(make_pair(v, w));
      g[v].push_back(make_pair(u, w));
   }

   vector <int> vis(N);
   vector <pair <int, int>> edges;
   function <int(int, int, int, int)> dfs = [&] (int limit, int print, int u, int iter) -> int {
      vis[u] = iter;
      int res = 1;
      for (auto vp : g[u]) {
         int v = vp.first;
         int w = vp.second;
         if (vis[v] != iter and w <= limit) {
            if (print) { edges.push_back(make_pair(u + 1, v + 1)); }
            res += dfs (limit, print, v, iter);
         }
      }
      return res;
   };

   int iter = 1;
   while (low <= high) {
      int guess = (low + high) / 2;
      if (dfs(guess, 0, 0, iter) == N) {
         high = guess - 1;
      }
      else { low = guess + 1; }
      ++iter;
   }
   cout << low << '\n';
   dfs (low, 1, 0, iter);
   cout << edges.size() << '\n';
   for (auto e : edges) {
      cout << e.first << ' ' << e.second << '\n';
   }
   return;
}


signed main()
{
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
