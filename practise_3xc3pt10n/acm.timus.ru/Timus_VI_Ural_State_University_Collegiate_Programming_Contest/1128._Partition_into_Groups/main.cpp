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
   vector<vector<int>> g;
   g.assign(N, vector <int> ());
   vector <vector <bool>> mat(N, vector <bool> (N));
   vector <int> deg(N);

   for (int u = 0; u < N; ++u) {
      int e; cin >> e;
      while (e--) {
          int v; cin >> v; --v;
          mat[v][u] = mat[u][v] = true;
          g[u].push_back(v);
          g[v].push_back(u);
          deg[u] += 1;
          deg[v] += 1;
      }
   }

   bool ok = false;
   vector <int> belong(N);

   // deg is max 3,
   // val -> 3, after moving becomes 0, neighbours' value  get reduced
   // val -> 2, after moving becomse 1, neighbours' value get reduced
   // val -> 0/1, leave it like that
   while (!ok)  {
      ok = true;
      vector <int> cnt(N);
      for (int u = 0; u < N; ++u) {
         for (int v = u + 1; v < N; ++v) {
            if (mat[u][v] and belong[u] == belong[v]) {
               cnt[u] += 1;
               cnt[v] += 1;
            }
         }
      }

      for (int u = 0; u < N; ++u) {
         for (int v : g[u]) {
            if (belong[v] == belong[u] and (cnt[u] > 1 or cnt[v] > 1)) {
               int uu = v;
               if (deg[u] - cnt[u] < deg[v] - cnt[v]) {
                  uu = u;
               }
               belong[uu] ^= 1;
               for (int vtemp : g[uu]) {
                  if (belong[vtemp] == belong[uu]) {
                     cnt[vtemp] += 1;
                     cnt[uu] += 1;
                  }
                  else {
                     cnt[vtemp] -= 1;
                     cnt[uu] -= 1;
                  }
               }
               ok = false;
            }
         }
      }
   }

   int firstGroupMark = belong[0];
   vector <int> firstGroupVec, otherGroupVec;
   for (int u = 0; u < N; ++u) {
      if (belong[u] == firstGroupMark) {
         firstGroupVec.push_back(u + 1);
      }
      else {
         otherGroupVec.push_back(u + 1);
      }
   }
   if (firstGroupVec.size() > otherGroupVec.size()) {
      swap(firstGroupVec, otherGroupVec);
   }
   cout << firstGroupVec.size() << '\n';
   for (int v : firstGroupVec) {
      cout << v << ' ';
   }
   cout << '\n';
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
