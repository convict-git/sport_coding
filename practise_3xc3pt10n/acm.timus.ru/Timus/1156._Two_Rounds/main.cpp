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
   N *= 2;
   vector <vector <int>> g;
   g.assign(N, vector <int> ());

   for (int e = 0; e < M; ++e) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      g[u].push_back(v);
      g[v].push_back(u);
   }

   bool ok = true;
   vector <bool> vis(N);
   vector <int> color(N);
   function <pair <vector <int>, vector <int>> (int, int)> dfs = [&] (int u, int c) {
      vis[u] = true;
      color[u] = c;
      pair <vector <int>, vector <int>> res;
      if (c) res.first.push_back(u);
      else res.second.push_back(u);

      for (int v : g[u]) {
         if (!vis[v] and ok) {
            auto go = dfs(v, c ^ 1);
            for (int vv : go.first) {
               res.first.push_back(vv);
            }
            for (int vv : go.second) {
               res.second.push_back(vv);
            }
         }
         else if (vis[v] and color[v] == color[u]) {
            ok = false;
         }
      }
      return res;
   };

   vector <pair <int, int>> ar;
   vector <pair <vector <int>, vector <int>>> work;
   for (int i = 0; i < N; ++i) {
      if (!vis[i]) {
         work.push_back(dfs (i, 0));
         auto p = make_pair(work.back().first.size(), work.back().second.size());
         ar.push_back(p);
      }
   }
   if (!ok) {
      cout << "IMPOSSIBLE\n";
      return;
   }

   int sz = (int)ar.size();

   // (a1, b1), (a2, b2), (a3, b3) .... (an, bn)
   // some way to select to make (N / 2, N / 2)
   vector <vector <int>> pi(sz + 1, vector <int> (N, -1));
   vector <vector <bool>> dp(sz + 1, vector <bool> (N));
   dp[0][0] = true; // is it possible?
   for (int pos = 0; pos < sz; ++pos) {
      for (int val = 0; val <= N; ++val) {
         // first
         if (val + ar[pos].first <= N and dp[pos][val]) {
            dp[pos + 1][val + ar[pos].first] = true;
            pi[pos + 1][val + ar[pos].first] = 0;
         }
         // second
         if (val + ar[pos].second <= N and dp[pos][val]) {
            dp[pos + 1][val + ar[pos].second] = true;
            pi[pos + 1][val + ar[pos].second] = 1;
         }
      }
   }

   if (dp[sz][N / 2] == false) {
      cout << "IMPOSSIBLE\n";
      return;
   }

   pair <vector <int>, vector <int>> res;
   int cur = N / 2;
   for (int pos = sz; pos >= 1; --pos) {
      if (pi[pos][cur] == 0) {
         cur -= ar[pos - 1].first;
         for (int v : work[pos - 1].first) {
            res.first.push_back(v);
         }
         for (int v : work[pos - 1].second) {
            res.second.push_back(v);
         }
      }
      else if (pi[pos][cur] == 1) {
         cur -= ar[pos - 1].second;
         for (int v : work[pos - 1].second) {
            res.first.push_back(v);
         }
         for (int v : work[pos - 1].first) {
            res.second.push_back(v);
         }
      }
      else { assert(false); }
   }
   assert((int)res.first.size() == N / 2 and (int)res.second.size() == N / 2);
   for (int v : res.first) { cout << v + 1 << ' '; } cout << '\n';
   for (int v : res.second) { cout << v + 1 << ' '; } cout << '\n';
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
