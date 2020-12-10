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

typedef long long Int;

void preproc()
{
}

void solve()
{
   int N;
   cin >> N;
   vector <vector <int>> T;
   T.assign(N, vector <int> ());

   vector <int> R(N);

   for (int u = 0; u < N; ++u) {
      cin >> R[u];
      int v;
      while (cin >> v, v) {
         --v;
         T[u].push_back(v);
         T[v].push_back(u);
      }
   }

   int vel, root;
   cin >> root >> vel;
   --root;

   vector <pair <Int, Int>> ome(N);
   vector <int> vis(N);
   vector <int> depth(N);

   ome[root] = {abs(vel), 1};

   function <void(int, int)> dfs = [&] (int u, int d) -> void {
      vis[u] = true;
      depth[u] = d;

      for (int v : T[u]) {
         if (!vis[v]) {
            Int num = ome[u].first * R[u];
            Int den = ome[u].second * R[v];
            Int gcdNM = __gcd(num, den);
            num /= gcdNM;
            den /= gcdNM;

            ome[v] = make_pair(num, den);
            dfs(v, d + 1);
         }
      }
   };

   dfs(root, 0);

   for (int i = 0; i < N; ++i){
      debug(depth[i], ome[i].first, ome[i].second);
      assert(ome[i].first >= 0 and ome[i].second >= 0);
      if (depth[i] % 2 == 1 and vel > 0) ome[i].first *= -1ll;
      if (depth[i] % 2 == 0 and vel < 0) ome[i].first *= -1ll;
      cout << ome[i].first << "/" << ome[i].second << '\n';
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
