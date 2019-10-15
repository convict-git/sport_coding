#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;
vector < vector <pii> > Adj;
const int N = int(1e6) + 10;
const int infi = int(1e9);
int n, m, dist[N];
bool vis[N];

class Compare {
   public:
      inline bool operator () (const int &p, const int &q) const {
         return dist[p] > dist[q];
      }
};

void dijkstra (int src) {
   for (int i = 0; i < n; ++i)
      dist[i] = infi, vis[i] = false;

   dist[src] = 0;

   priority_queue <int, vector <int>, Compare> Q;
   Q.push(src);

   while (!Q.empty()) {
      int u = Q.top();
      Q.pop();
      if (vis[u]) continue;
      vis[u] = true;

      for (auto vPair : Adj[u]) {
         int v = vPair.x, w = vPair.y;
         if (!vis[v] && dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            Q.push(v);
         }
      }
   }

   int mx = INT_MIN;
   for (int i = 0; i < n; ++i) {
      if (dist[i] == infi) continue;
      mx = max(dist[i], mx);
   }

   int cnt = 0;
   for (int i = 0; i < n; ++i) {
      if (dist[i] == mx) ++cnt;
   }
   cout << mx << ' ' << cnt << '\n';
}

void read () {
   int q, u, v, w;
   while (cin >> n >> m >> q) {
      Adj.resize(n, vector <pii> ());
      vector <pair <pii, int> > edges;

      for (int e = 0; e < m; ++e) {
         cin >> u >> v >> w;
         if (u == v) continue;
         edges.push_back(pair <pii, int> (pii(u, v), w));
      }
      sort (edges.begin(), edges.end());
      set <pii> ed;

      for (auto Edge : edges) {
         if (ed.find(Edge.x) == ed.end()) {
            ed.insert(Edge.x);
            u = Edge.x.x, v = Edge.x.y, w = Edge.y;
            Adj[u].emplace_back(pii(v, w));
            Adj[v].emplace_back(pii(u, w));
         }
      }

      int src;
      for (int i = 0; i < q; ++i) {
         cin >> src;
         dijkstra (src);
      }
   }
}

signed main() {
   read();

   return EXIT_SUCCESS;
}

