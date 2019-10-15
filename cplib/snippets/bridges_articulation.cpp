// bridges and articulation points library
// This library is created by Priyanshu Shrivastav (mr.convict)
// https://github.com/convict-git/sport_coding/blob/master/cplib/snippets/graph.cpp
#include <bits/stdc++.h>
using namespace std;

class graph {
   public:
      static const int N = (int)2e5 + 10;
      static const int inf_int = (int)1e9;
      static const long long inf_ll = (long long)1e18;
      /* -------------------------------------------------- */

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

      long long dist_s[N];
      int pi[N];

      set < pair <int, int> > bridge_edges; // bridge edges stored in set
      set <int> cut_vertices; // articulation points store in set

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

      void find_bridge_edges() {
         int tmr = 0;
         int f[N], t[N];

         fill (vis, vis + V, false);
         fill (t, t + V, -1);
         fill (f, f + V, -1);

         bridge_edges.clear();

         function <void(int, int)> dfs_f;
         dfs_f = [&] (int u, int pr) -> void {
            vis[u] = true;
            t[u] = f[u] = tmr++;

            for (Edge e : adj[u]) {
               int v = e.v;
               if (v == pr) continue;
               if (vis[v])
                  f[u] = min (f[u], t[v]);
               else {
                  dfs_f (v, u);
                  f[u] = min (f[u], f[v]);
                  if (f[v] > t[u]) {
                     bridge_edges.insert({u, v});
                     bridge_edges.insert({v, u});
                  }
               }
            }
         };

         for (int u = 0; u < V; ++u) {
            if (!vis[u]) dfs_f (u, -1);
         }
      }

      /* -------------------------------------------------- */

      void find_cut_vertex() {
         int tmr = 0;
         int f[N], t[N], tree_deg[N];

         fill(vis, vis + V, false);
         fill(tree_deg, tree_deg + V, 0);
         fill(f, f + V, -1);
         fill(t, t + V, -1);

         cut_vertices.clear();

         function <void(int, int)> dfs_f;
         dfs_f = [&] (int u, int pr) -> void {
            vis[u] = true;
            f[u] = t[u] = tmr++;

            for (Edge e : adj[u]) {
               int v = e.v;
               if (v == pr) continue;
               if (vis[v])
                  f[u] = min(f[u], t[v]);
               else {
                  ++tree_deg[u];
                  dfs_f (v, u);
                  f[u] = min(f[u], f[v]);

                  if (f[v] >= t[u] && pr != -1) //careful : u shouldn't be root here
                     cut_vertices.insert(u);

               }
               if (pr == -1 && tree_deg[u] > 1) // case of u is root
                  cut_vertices.insert(u);
            }
         };

         for (int u = 0; u < V; ++u)
            if (!vis[u]) dfs_f (u, -1);
      }
};

