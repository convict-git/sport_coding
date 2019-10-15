// GRAPH library
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

      vector <int> topological_order;

      long long dist_s[N];
      int pi[N];

      int cc_total, cc_idx[N];
      vector < vector <int> > cc_components;
      vector < set <int> > adj_cc;

      set < pair <int, int> > bridge_edges;
      set <int> cut_vertices;

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

      bool bfs (int src, int dest = -1) {
         fill(dist_s, dist_s + V, inf_int);
         fill(vis, vis + V, false);
         fill(pi, pi + V, -1);
         queue <int> Q;

         vis[src] = true;
         dist_s[src] = 0;

         Q.push(src);
         while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            if (dest != -1 && u == dest) break;
            for (Edge e : adj[u]) {
               int v = e.v;
               if (!vis[v]) {
                  vis[v] = true;
                  Q.push(v);
                  dist_s[v] = dist_s[u] + 1;
                  pi[v] = u;
               }
            }
         }
         return (dest != -1 && dist_s[dest] != inf_int);
      }

      /* -------------------------------------------------- */

      vector <int> path_vector_s (int dest) {
         vector <int> path_v;
         if (vis[dest]) {
            int tmp = dest;
            while (tmp != -1) {
               path_v.push_back(tmp);
               tmp = pi[tmp];
            }
            reverse(path_v.begin(), path_v.end());
            for (int p : path_v) cout << p << ' ';
            cout << '\n';
         }
         else {
            cout << "not reachable\n";
         }
         return path_v;
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

      /* -------------------------------------------------- */

      bool spfa (int src) {
         vector <int> in_queue (V, false);
         int cnt[N];

         fill(cnt, cnt + V, 0);
         fill(pi, pi + V, -1);
         fill(dist_s, dist_s + V, inf_ll);

         queue <int> Q;
         Q.push(src);
         dist_s[src] = 0;
         in_queue[src] = true;

         while (!Q.empty()) {
            int u = Q.front();
            Q.pop();
            in_queue[u] = false;

            for (Edge e : adj[u]) {
               int v = e.v;
               long long w = e.w;

               if (dist_s[u] != inf_ll && dist_s[v] > dist_s[u] + w) {
                  dist_s[v] = dist_s[u] + w;
                  pi[v] = u;
                  if (!in_queue[v]) {
                     Q.push(v);
                     in_queue[v] = true;
                     ++cnt[v];
                     if (cnt[v] > V) return false;
                  }
               }
            }
         }
         return true;
      }

      /* -------------------------------------------------- */

      bool bellmanford(int src) {
         fill(dist_s, dist_s + V, inf_ll);
         dist_s[src] = 0;

         for (int iter = 0; iter < V + 1; ++iter) {
            bool relax = false;
            for (Edge e : edges) {
               if (dist_s[e.u] < inf_ll && dist_s[e.v] > dist_s[e.u] + e.w) {
                  dist_s[e.v] = dist_s[e.u] + e.w;
                  relax = true;
               }
            }
            if (!relax) break;
            if (iter == V && relax) return false;
         }
         return true;
      }

      /* -------------------------------------------------- */

      void dijkstra (int src) {
         using pli = pair <long long, int>;

         fill(dist_s, dist_s + V, inf_ll);
         fill(vis, vis + V, false);
         fill(pi, pi + V, -1);

         dist_s[src] = 0;
         priority_queue < pli, vector <pli>, greater <pli> > Q;

         for (int u = 0; u < V; ++u) {
            Q.push (make_pair(dist_s[u], u));
         }

         while (!Q.empty()) {
            int u = Q.top().second;
            Q.pop();
            if (vis[u]) continue;
            vis[u] = true;

            for (Edge e : adj[u]) {
               int v = e.v;
               long long w = e.w;
               if (dist_s[v] > dist_s[u] + w) {
                  dist_s[v] = dist_s[u] + w;
                  pi[v] = u;
                  Q.push (make_pair(dist_s[v], v));
               }
            }
         }
      }

      /* -------------------------------------------------- */

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

         for (Edge e : edges) {
            int u = e.u, v = e.v;
            long long w = e.w;
            if (find_set(u) == find_set(v)) continue;
            cost += w;
            merge_set(u, v);
            MST.push_back(e);
            ++edge_cnt_mst;
         }

         assert (edge_cnt_mst == V - 1);
         return cost;
      }

      /* -------------------------------------------------- */
};

/* -------------------------------------------------------------------------- */
