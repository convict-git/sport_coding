#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

int V, E, src, tar;
vector < vector <pii> > Adj;

const int infi = (int)1e9;
const int N = int(1e5) + 10;
int dist[N];

struct tup {
   int v, wt, state;
   inline bool operator > (const tup &p) const {
      return wt > p.wt;
   }
};

void modDijkstra() {
   bool vis[N][2];
   priority_queue < tup, vector <tup>, greater <tup> > Q;

   for (int i = 0; i < V; ++i)
      dist[i] = infi, vis[i][0] = vis[i][1] = false;
   dist[src] = 0;
   Q.push({src, 0, 0});
   Q.push({src, 0, 1});

   while (!Q.empty()) {
      tup tmp = Q.top();
      Q.pop();
      int u = tmp.v, state = tmp.state;
      int idx = (u == src ? state : 0);
      if (vis[u][idx]) continue;
      vis[u][idx] = true;

      for (auto vPair : Adj[u]) {
         int v = vPair.x;
         int st = vPair.y;
         if (!vis[v][0] && dist[v] > dist[u] + (state ^ st)) {
            dist[v] = dist[u] + (state ^ st);
            Q.push({v, dist[v], st});
         }
      }
   }

   assert (dist[tar] != infi);
   cout << dist[tar] << '\n';
}

void read() {
   int n, m, u, v;
   cin >> n >> m;
   V = n, E = m;
   Adj.assign(V, vector <pii>());

   for (int e = 0; e < m; ++e) {
      cin >> u >> v;
      --u, --v;
      Adj[u].emplace_back(pii(v, 0)); // 0 for up // 1 for down
      Adj[v].emplace_back(pii(u, 1));
   }
   cin >> src >> tar;
   --src, --tar;
}

signed main() {
   read();
   modDijkstra();
   return EXIT_SUCCESS;
}

