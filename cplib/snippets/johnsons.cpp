#include <bits/stdc++.h>
using namespace std;
struct Edge {
   int u, v, w;
   inline bool operator < (const Edge &o) const {
      return w < o.w;
   }
};

vector <Edge> edges;
vector < vector <pii> > Adj;
int h[N], d[N][N];
int n, m;

void init() {
   assert(n);
   Adj.assign(n, vector <pii> ());
   edges.clear();
   for (int i = 0; i < n; ++i) {
      h[i] = infi;
      for (int j = 0; j < n; ++j) d[i][j] = infi;
   }
}

bool bellmanFord() {
   for (int i = 0; i < n + 1; ++i) {
      for (Edge e : edges) {
         if (h[e.u] < infi && h[e.v] > h[e.u] + e.w) {
            h[e.v] = h[e.u] + e.w;
            if (i == n) return false;
         }
      }
   }
   return true;
}

void dijkstra(int s, int dist[]) {
   bool vis[N] = {0};
   priority_queue <pii, vector <pii>, greater <pii> > Q;
   fill (dist, dist + n, infi);
   dist[s] = 0;
   Q.push(pii(dist[s], s));

   while (!Q.empty()) {
      pii tmp = Q.top();
      Q.pop();
      int u = tmp.y;
      if (vis[u]) continue;

      for (auto vPair : Adj[u]) {
         int v = vPair.x, w = vPair.y;
         if (!vis[v] && dist[u] < infi && dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            Q.push(pii(dist[v], v));
         }
      }
   }
}

bool johnsons() {
   for (int i = 0; i < n; ++i) {
      edges.push_back({n, i, 0});
   }
   h[n] = 0;
   fill (h, h + n, infi);
   bool ok = bellmanFord();
   if (!ok) return false;

   for (Edge e : edges) {
      if (e.u == n) continue;
      Adj[e.u].push_back(pii(e.v, e.w - h[e.u] + h[e.v]));
   }

   for (int i = 0; i < n; ++i)
      dijkstra(i, d[i]);

   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
         if (d[i][j] == infi) continue;
         d[i][j] += h[i] - h[j];
      }
   }
   return true;
}
