#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = (int)1e3 + 10;
const int infi = (int)1e9;
vector < vector <pii> > Adj, AdjT;
vector < pair <pii, int> > edges;
int n, m, src, tar;

int ds[N], dt[N];
bool vis[N];

void dijkstra (int s, int d[], vector < vector <pii> > &Ad) {
   for (int i = 0; i < n; ++i)
      d[i] = infi, vis[i] = false;

   priority_queue < pii, vector <pii>, greater <pii> > Q;
   d[s] = 0;
   Q.push(pii(d[s], s));

   while (!Q.empty()) {
      pii tmp = Q.top();
      Q.pop();
      int u = tmp.y;
      if (vis[u]) continue;
      vis[u] = true;

      for (auto vPair : Ad[u]) {
         int v = vPair.x;
         int w = vPair.y;

         if (!vis[v] && d[v] > d[u] + w) {
            d[v] = d[u] + w;
            Q.push(pii(d[v], v));
         }
      }
   }
}


void read() {
   while (cin >> n >> m, n || m) {
      Adj.assign(n, vector <pii>());
      AdjT.assign(n, vector <pii>());
      edges.clear();

      cin >> src >> tar;
      int u, v, w;
      for (int i = 0; i < m; ++i) {
         cin >> u >> v >> w;
         edges.emplace_back(pair <pii, int> (pii(u, v), w));
         Adj[u].emplace_back(pii(v, w));
         AdjT[v].emplace_back(pii(u, w));
      }

      dijkstra(src, ds, Adj);
      dijkstra(tar, dt, AdjT);
      assert (ds[tar] == dt[src]);

      Adj.assign(n, vector <pii> ());
      for (auto Edge : edges) {
         u = Edge.x.x, v = Edge.x.y, w = Edge.y;
         if (ds[u] + dt[v] + w == ds[tar] || ds[v] + dt[u] + w == ds[tar])
            continue;
         Adj[u].emplace_back(pii(v, w));
      }

      dijkstra(src, ds, Adj);
      if (ds[tar] == infi) cout << -1 << '\n';
      else cout << ds[tar] << '\n';
   }
}

signed main() {
   read();
   return EXIT_SUCCESS;
}

