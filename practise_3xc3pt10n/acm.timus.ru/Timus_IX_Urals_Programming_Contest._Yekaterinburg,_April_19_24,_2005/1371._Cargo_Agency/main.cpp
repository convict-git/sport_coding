#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (12); cout << fixed
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
   vector <vector <pair <int, int>>> T;
   T.assign(N, vector<pair <int, int>> ());

   for (int i = 0; i < N - 1; ++i) {
      int a, b, c;
      cin >> a >> b >> c;
      --a, --b;
      T[a].push_back({b, c});
      T[b].push_back({a, c});
   }

   long double res = 0;

   vector <bool> vis(N);
   function <int (int)> dfs = [&] (int u) -> int {
      vis[u] = true;
      int sm_childs = 0;
      for (auto p : T[u]) {
         int v = p.first;
         int c = p.second;
         if (!vis[v]) {
            int cur_value = dfs(v);
            sm_childs += cur_value + 1;
            res += ((long double) (cur_value + 1)) * (N - 1 - cur_value) * c;
         }
      }
      return sm_childs;
   };

   dfs(0);
   vector <int> v;

   cout << (res * 2) / (1ll * N * (N - 1)) << '\n';
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
