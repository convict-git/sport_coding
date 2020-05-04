#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;
const int N = (int)1e2 + 10;
const int infi = (int)1e9;

int n, m;
vector < vector <pii> > Adj;
int dist[N][N];

void dijkstra(int src, int d[]) {
   bool vis[N];
   for (int i = 0; i < n; ++i)
      d[i] = infi, vis[i] = false;

   priority_queue <pii, vector <pii>, greater <pii> > Q;
   d[src] = 0;
   Q.push(pii(d[src], src));

   while (!Q.empty()) {
      pii tmp = Q.top();
      Q.pop();
      int u = tmp.y;
      if (vis[u]) continue;
      vis[u] = true;

      for (auto vPair : Adj[u]) {
         int v = vPair.x;
         int w = vPair.y;

         if (!vis[v] && d[v] > d[u] + w) {
            d[v] = d[u] + w;
            Q.push(pii(d[v], v));
         }
      }
   }
}

inline bool isPoint (int s) {
   for (int i = 1; i < 5; ++i) {
      if (dist[i][s] != dist[0][s]) return false;
   }
   return true;
}

void solve(int tc) {
   for (int i = 0; i < n; ++i) {
      dijkstra(i, dist[i]);
   }

   vector <int> points;
   for (int i = 5; i < n; ++i) {
      if (isPoint(i)) points.push_back(i);
   }

   int mn = infi;
   for (int p : points) {
      int Mx = -infi;
      for (int i = 0; i < n; ++i) {
         Mx = max(Mx, dist[p][i]);
      }
      mn = min(mn, Mx);
   }

   cout << "Map " << tc << ": " << (mn == infi ? -1 : mn) << '\n';
}

void read() {
   cin >> n >> m;
   Adj.assign(n, vector <pii> ());

   int u, v, c;
   for (int i = 0; i < m; ++i) {
      cin >> u >> v >> c;
      --u, --v;
      Adj[u].push_back(pii(v, c));
      Adj[v].push_back(pii(u, c));
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

