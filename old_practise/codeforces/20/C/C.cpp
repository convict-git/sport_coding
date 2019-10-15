#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
using namespace std;

const int maxn = 1e5 + 10;
const long long inf = (long long) 1e18;

// Dijkstra library
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
      vector <int> path_vector_s (int dest) {
         vector <int> path_v;
         if (vis[dest]) {
            int tmp = dest;
            while (tmp != -1) {
               path_v.push_back(tmp);
               tmp = pi[tmp];
            }
            reverse(path_v.begin(), path_v.end());
            for (int p : path_v) cout << p + 1 << ' ';
            cout << '\n';
         }
         else {
            cout << "not reachable\n";
         }
         return path_v;
      }
};
int n, m;


int main() {
	IOS; PREC;

	cin >> n >> m;
   graph g(n);

	for (int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		if (u == v) continue;
      g.add_edge(u, v, w);
	}

	g.dijkstra (0);
   if (g.dist_s[n - 1] == g.inf_ll) {
      cout << -1 << '\n';
   }
   else {
      g.path_vector_s(n - 1);
   }

	return EXIT_SUCCESS;
}

