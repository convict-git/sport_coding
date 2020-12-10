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
   int N;
   cin >> N;
   vector <vector <int>> T(N, vector <int> ());
   for (int i = 0; i < N-1; ++i) {
      int u, v;
      cin >> u >> v; --u, --v;
      T[u].push_back(v);
      T[v].push_back(u);
   }

   vector <int> cnt(N), maxdp(N);
   vector <bool> vis(N, false);

   function <void(int)> dfs = [&] (int u) -> void {
      vis[u] = true;
      int mx = 0;
      for (int v : T[u]) if (!vis[v]) {
         dfs(v);
         cnt[u] += cnt[v];
         mx = max(mx, cnt[v]);
      }
      cnt[u] += 1;
      maxdp[u] = max(N - cnt[u], mx);
      return;
   };

   dfs(0);
   debug(maxdp);
   int mx_group = *min_element(maxdp.begin(), maxdp.end());

   vector <int> centroids;
   for (int i = 0; i < N; ++i) {
      if (maxdp[i] == mx_group) {
         centroids.push_back(i);
      }
   }
   debug(centroids.size());
   if (centroids.size() == 1) {
      cout << 1 << ' ' << T[0][0] + 1 << '\n';
      cout << 1 << ' ' << T[0][0] + 1 << '\n';
      return;
   }

   int c1 = centroids[0], c2 = centroids[1];
   vis.assign(N, false);

   int leaf_par, leaf_child;
   bool found = false;
   function <void(int)> find_leaf = [&] (int u) -> void {
      vis[u] = true;

      for (int v : T[u]) {
         if (v != c2 and !vis[v] and !found) {
            find_leaf(v);
            if ((int)T[v].size() == 1) {
               leaf_par = u;
               leaf_child = v;
               found = true;
            }
         }
      }
   };

   find_leaf(c1);
   cout << leaf_par + 1 << ' ' << leaf_child + 1 << '\n';
   cout << leaf_child + 1 << ' ' << c2 + 1 << '\n';
}

signed main()
{
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
