#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    "[ " << #x << " : " << x << " ]"
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = 105;
const int infi = (int)1e9;

struct Edge {
   int u, v, w;
};
vector <Edge> edges;
vector < vector <pii> > Adj;

int h[N], d[N][N];
int n, m;

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

void solve(int tc) {
   //finding h
   for (int i = 0; i < n; ++i) {
      edges.push_back({n, i, 0});
   }
   h[n] = 0;
   fill (h, h + n, infi);
   bool ok = bellmanFord();
   if (!ok) {
      cout << "graph " << tc << " no\n";
   }
   else {
      cout << "graph " << tc << " yes\n\n";
      for (int i = 0; i < n + 1; ++i)
         cout << h[i] << " \n"[i == n];
      cout << '\n';

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
      for (int i = 0; i < n; ++i) {
         for (int j = 0; j < n; ++j) {
            if (d[i][j] == infi) cout << "# ";
            else cout << d[i][j] << ' ';
         }
         cout << '\n';
      }
   }
   cout << '\n';
}

void read() {
   cin >> n >> m;
   edges.clear();
   Adj.assign(n, vector <pii> ());

   int u, v, w;
   for (int i = 0; i < m; ++i) {
      cin >> u >> v >> w;
      --u, --v;
      edges.push_back({u, v, w});
   }
}

signed main() {
   int tc;
   cin >> tc;
   for (int i = 1; i <= tc; ++i) {
      read();
      solve(i);
   }

   return EXIT_SUCCESS;
}

