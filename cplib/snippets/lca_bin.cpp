#include      <bits/stdc++.h>
using namespace std;

class LCA { /*{{{*/
   // LCA library using binary lifting + dp using binary lifting
   // This library is created by Priyanshu Shrivastav (mr.convict)
   // https://github.com/convict-git/sport_coding/blob/master/cplib/snippets/lca_bin.cpp
   public:
   int V;
   const int D = 21; // for handling n upto 2e6
   vector <vector <int>> table, dp;
   vector <int> depth;

   inline int walk(int u, int k) {
      for (int d = 0; d <= D && u != -1; ++d) {
         if ((1 << d) & k) {
            u = table[u][d];
         }
      }
      return u;
   }

   LCA(int n, vector <vector<pair <int, int>>> &T, int root = 0, int OP=0) {
      V = n;
      table.assign(n, vector <int>(D + 1, -1));
      dp.assign(n, vector <int>(D + 1, INT_MAX));
      depth.assign(n, 0);

      function <void(int, int, int)> dfs =
         [&](int u, int pr, int d) -> void {
            depth[u] = d;
            for (auto v_pair : T[u]) {
               int v = v_pair.first;
               int w = v_pair.second;
               if (v == pr) continue;
               table[v][0] = u;
               dp[v][0] = w;
               dfs(v, u, d + 1);
            }
         };

      dfs(root, -1, 0);

      for (int k = 1; k <= D; ++k) {
         for (int i = 0; i < n; ++i) {
            if (table[i][k - 1] == -1) continue;
            table[i][k] = table[table[i][k - 1]][k - 1];
            dp[i][k] = min(dp[i][k - 1], dp[table[i][k - 1]][k - 1]);
         }
      }
   }

   int find_lca(int u, int v) {
      if (depth[u] > depth[v]) {
         u = walk(u, depth[u] - depth[v]);
      }
      else if (depth[u] < depth[v]) {
         v = walk(v, depth[v] - depth[u]);
      }
      if (u == v) return u;

      for (int d = D; d >= 0; --d) {
         if (table[u][d] != table[v][d]) {
            u = table[u][d];
            v = table[v][d];
         }
      }
      return table[u][0];
   }

   int get_min_edge (int u, int v) {
      auto walk_get_min = [&] (int &i, int k) -> int {
         int mn = INT_MAX;
         for (int d = 0; d <= D && i >= 0; ++d) {
            if ((1 << d) & k) {
               mn = min(mn, dp[i][d]);
               i = table[i][d];
            }
         }
         return mn;
      };

      int mn = INT_MAX;
      if (depth[u] > depth[v]) {
         mn = walk_get_min(u, depth[u] - depth[v]);
      }
      if (depth[v] > depth[u]) {
         mn = walk_get_min(v, depth[v] - depth[u]);
      }
      if (u == v) return mn;
      for (int d = D; d >= 0; --d) {
         if (table[u][d] != table[v][d]) {
            mn = min({mn, dp[u][d], dp[v][d]});
            u = table[u][d]; // updates
            v = table[v][d];
         }
      }
      mn = min({mn, dp[u][0], dp[v][0]});
      return mn;
   }
}; /*}}}*/
