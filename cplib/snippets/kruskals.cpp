// kruskals library
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
      vector <Edge> edges;
      int deg[N];

      long long dist_s[N];
      int pi[N];

      vector <Edge> MST;

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
         edges.push_back({u, v, w, id});
         ++deg[u];

         if (IS_UNDIR) {
            adj[v].push_back({v, u, w, id});
            adj_rev[u].push_back({u, v, w, id});
            edges.push_back({v, u, w, id});
            ++deg[v];
         }
      }

      long long kruskals () {
         assert(IS_UNDIR);
         MST.clear();
         int rep[N], rnk[N];

         for(int u = 0; u < V; ++u)
            rep[u] = u, rnk[u] = 0;

         function <int(int)> find_set = [&] (int u) -> int {
            int ru = u;
            while (ru != rep[ru])
               ru = rep[ru];

            while (u != rep[u]) {
               int tmp = rep[u];
               rep[u] = ru;
               u = tmp;
            }
            return ru;
         };

         function <void(int, int)> merge_set = [&] (int u, int v)->void {
            int ru = find_set(u), rv = find_set(v);
            if (rnk[ru] > rnk[rv]) rep[rv] = rep[ru];
            else rep[ru] = rep[rv];

            if (rnk[ru] == rnk[rv])
               ++rnk[rv];
         };


         long long cost = 0;
         int edge_cnt_mst = 0;
         sort(edges.begin(), edges.end());

         for (Edge e : edges) {
            int u = e.u, v = e.v;
            long long w = e.w;
            if (find_set(u) == find_set(v)) continue;
            cost += w;
            merge_set(u, v);
            MST.push_back(e);
            ++edge_cnt_mst;
         }

         // assert (edge_cnt_mst == V - 1);
         return cost;
      }
};

/* -------------------------------------------------------------------------- */
