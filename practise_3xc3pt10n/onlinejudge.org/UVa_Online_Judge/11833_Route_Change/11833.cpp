#include         <bits/stdc++.h>
#define x        first
#define y        second
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
using namespace std;
using pii = pair <int, int>;
int n, m, c, k;


const int N = (int)1e3 + 10;
const int infi = (int)1e9;

vector <vector <pii> > Adj;
int dt[N], dk[N];
bool vis[N];

void dijkstra(int s, int d[]) {
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

      for (auto vPair : Adj[u]) {
         int v = vPair.x;
         int w = vPair.y;

         if (!vis[v] && d[v] > d[u] + w) {
            d[v] = d[u] + w;
            if (v >= c) Q.push(pii(d[v], v));
         }
      }
   }
}

void solve() {
   dt[c - 1] = 0;
   for (int i = c - 2; i >= 0; --i) {
      for (auto vPair : Adj[i + 1]) {
         int v = vPair.x, w = vPair.y;
         if (v != i) continue;
         dt[i] = dt[i + 1] + w;
      }
   }

   dijkstra (k, dk);
   int mn = infi;

   for (int i = 0; i < c; ++i) {
      mn = min (mn, dk[i] + dt[i]);
   }
   cout << mn << '\n';
}


void read() {
   while (cin >> n >> m >> c >> k, n || m || c || k) {
      Adj.assign(n, vector <pii>());

      int u, v, w;
      for (int i = 0; i < m; ++i) {
         cin >> u >> v >> w;
         Adj[u].emplace_back(pii(v, w));
         Adj[v].emplace_back(pii(u, w));
      }
      solve();
   }
}

signed main() {
   read();

   return EXIT_SUCCESS;
}

