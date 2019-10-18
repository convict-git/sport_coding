#include <bits/stdc++.h>
using namespace std;

class graph { /*{{{*/
   // BFS library
   // This library is created by Priyanshu Shrivastav (mr.convict)
   // https://github.com/convict-git/sport_coding/blob/master/cplib/snippets/graph.cpp
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
      vector <Edge> edges;
      int deg[N];

      long long dist_s[N];
      int pi[N];

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
}; /*}}}*/

