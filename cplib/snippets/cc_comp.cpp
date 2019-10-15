// cc_comp library
// This library is created by Priyanshu Shrivastav (mr.convict)
// https://github.com/convict-git/sport_coding/blob/master/cplib/snippets/graph.cpp
#include <bits/stdc++.h>
using namespace std;

class graph {
   public:
      static const int N = (int)2e5 + 10;
      static const int inf_int = (int)1e9;
      static const long long inf_ll = (long long)1e18;

      struct Edge {
         int u, v;
         long long w;
         int id;
         inline bool operator < (const Edge &o) const {
            return w < o.w;
         }
      };

      bool IS_UNDIR, vis[N];
      int V;
      vector <vector <Edge>> adj, adj_rev;
      set <Edge> edges;
      int deg[N];

      vector <int> topological_order;

      long long dist_s[N];
      int pi[N];

      int cc_total, cc_idx[N];
      vector < vector <int> > cc_components;
      vector < set <int> > adj_cc;

      graph (int n, bool undir = true) {
         V = n;
         adj.assign(n, vector <Edge> ());
         adj_rev.assign(n, vector <Edge> ());
         fill(dist_s, dist_s + V, inf_int);
         fill(deg, deg + V, 0);
         IS_UNDIR = undir;
      }

      inline void add_edge (int u, int v, long long w = 1, int id = -1) {
         assert(v != u);
         adj[u].push_back({u, v, w, id});
         adj_rev[v].push_back({v, u, w, id});
         edges.insert({u, v, w, id});
         ++deg[u];

         if (IS_UNDIR) {
            adj[v].push_back({v, u, w, id});
            adj_rev[u].push_back({u, v, w, id});
            edges.insert({v, u, w, id});
            ++deg[v];
         }
      }

      /* -------------------------------------------------- */

      void topological_sort () {
         fill(vis, vis + V, false);
         topological_order.clear();

         function <void(int)> dfs_timer;
         dfs_timer = [&] (int u) -> void {
            vis[u] = true;

            for (Edge e : adj[u]) {
               int v = e.v;
               if (!vis[v]) dfs_timer (v);
            }
            topological_order.push_back(u);
         };

         for (int u = 0; u < V; ++u)
            if (!vis[u]) dfs_timer(u);
         return;
      }

      /* -------------------------------------------------- */

      void cc_comp_dir() {
         assert(!IS_UNDIR);
         cc_total = 0;
         cc_components.clear();
         fill(cc_idx, cc_idx + V, -1);
         fill(vis, vis + V, false);

         function <void(int)> dfs_cc;
         dfs_cc = [&] (int u) -> void {
            vis[u] = true;
            cc_idx[u] = cc_total;
            cc_components[cc_total].push_back(u);

            for (Edge e : adj_rev[u]) {
               int v = e.v;
               if (!vis[v]) dfs_cc(v);
            }
         };

         topological_sort();

         fill (vis, vis + V, 0);
         reverse (topological_order.begin(), topological_order.end());
         for (int u : topological_order) {
            if (!vis[u]) {
               cc_components.push_back(vector <int> ());
               dfs_cc (u);
               ++cc_total;
            }
         }

         reverse (topological_order.begin(), topological_order.end());

         // the condensed graph (dag)
         adj_cc.assign(cc_total, set <int>());
         for (int u = 0; u < V; ++u) {
            for (Edge e : adj[u]) {
               int v = e.v;
               if (cc_idx[u] == cc_idx[v]) continue;
               adj_cc[cc_idx[u]].insert(cc_idx[v]);
            }
         }
      }

      /* -------------------------------------------------- */

      void cc_comp_undir () {
         assert(IS_UNDIR);
         cc_total = 0;
         fill(vis, vis + V, false);
         fill(cc_idx, cc_idx + V, -1);

         cc_components.clear();

         function <void(int)> dfs_cc;
         dfs_cc = [&] (int u) -> void {
            vis[u] = true;
            cc_idx[u] = cc_total;
            cc_components[cc_total].push_back(u);

            for (Edge e : adj[u]) {
               int v = e.v;
               if (!vis[v])
                  dfs_cc (v);
            }
         };

         for (int u = 0; u < V; ++u) {
            if (!vis[u]) {
               cc_components.push_back(vector <int>());
               dfs_cc (u);
               ++cc_total;
            }
         }
      }
};

