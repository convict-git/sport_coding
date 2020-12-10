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
   int N, remCost, addCost;
   cin >> N >> remCost >> addCost;
   vector <vector <int>> g;
   g.assign(N, vector <int> ());
   vector <string> mat(N);
   vector <int> deg(N);
   for (int i = 0; i < N; ++i) {
      cin >> mat[i];
      for (int j = 0; j < N; ++j) {
         if (mat[i][j] == '1') {
            g[i].push_back(j);
            ++deg[i];
         }
      }
   }

   vector <int> vis(N);
   function <void(int)> dfs = [&] (int u) {
      vis[u] = true;
      for (int v : g[u]) {
         if (!vis[v]) {
            mat[u][v] = mat[v][u] = 'x';
            dfs (v);
         }
      }
   };

   long long res = 0;
   vector <int> repMem;
   for (int u = 0; u < N; ++u) {
      if (!vis[u]) {
         repMem.push_back(u);
         dfs(u);
      }
   }

   for (int i = 0; i < N; ++i) {
      for (int j = i + 1; j < N; ++j) {
         if (mat[i][j] == '1') {
            mat[i][j] = mat[j][i] = 'd';
            res += remCost;
         }
         else if (mat[i][j] == 'x') {
            mat[i][j] = mat[j][i] = '0';
         }
         else {}  // Nothing
      }
   }

   for (int i = 0; i < (int)repMem.size() - 1; ++i) {
      mat[repMem[i]][repMem[i + 1]] = 'a';
      mat[repMem[i + 1]][repMem[i]] = 'a';
      res += addCost;
   }
   cout << res << endl;
   for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
         cout << mat[i][j];
      }
      cout << '\n';
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
