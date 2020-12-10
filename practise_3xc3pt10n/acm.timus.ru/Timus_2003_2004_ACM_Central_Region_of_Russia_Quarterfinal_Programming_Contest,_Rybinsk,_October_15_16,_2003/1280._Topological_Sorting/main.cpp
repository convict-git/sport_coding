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

int N, M;
vector <vector<int>> g;
vector <vector <bool>> dep;
vector <bool> vis;

void preproc()
{
}

void dfs (int s, int u) {
   dep[s][u] = true;
   vis[u] = true;
   for (int v : g[u]) {
      if (!vis[v]) {
         dfs (s, v);
      }
   }
}

void solve()
{
   cin >> N >> M;
   g.assign(N, vector <int> ());

   for (int e = 0; e < M; ++e) {
      int si, ui;
      cin >> si >> ui;
      --si, --ui;
      g[ui].push_back(si);
   }

   dep.assign(N, vector <bool> (N));
   // dep[u][v] -> u is dependent on v ?

   for (int u = 0; u < N; ++u) {
      vis.assign(N, false);
      dfs (u, u);
   }

   vector <int> order(N);
   for (int i = 0; i < N; ++i) {
      cin >> order[i];
      --order[i];
   }

   for (int i = 0; i < N; ++i) {
      for (int j = i + 1; j < N; ++j) {
         if (dep[order[i]][order[j]]) {
            cout << "NO\n";
            return;
         }
      }
   }
   cout << "YES\n";
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
