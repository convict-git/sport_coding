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
   int N, src;
   cin >> N >> src;
   --src;
   vector <vector<int>> mat;
   mat.assign(N, vector <int> (N));

   for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
         cin >> mat[i][j];
      }
   }

   // 1's are mark visited
   // start dfs from src, in dfs if taking u->v but v->u is already visited, then go on,
   // otherwise always go backwards and take v->u

   vector <pair <int, int>> edges;
   function <void(int, int)> dfs = [&] (int u, int pr) -> void {
      if (pr != -1 and mat[u][pr] == 0) {
         mat[u][pr] = 1;
         edges.push_back(make_pair(u, pr));
         dfs(pr, u);
         return;
      }
      for (int v = 0; v < N; ++v) {
         if (v == u or v == pr) continue;
         if (mat[u][v] == 0) {
            mat[u][v] = 1;
            edges.push_back(make_pair(u, v));
            dfs(v, u);
            return;
         }
      }
   };
   dfs(src, -1);
   for (auto e : edges) {
      cout << e.first + 1 << ' ' << e.second + 1 << '\n';
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
