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

const int infi = (int)1e9;
const int N = 105;
const int M = 2010;

struct edge {
   int v, w, id;
   inline bool operator > (const edge& oth) const {
      return w > oth.w;
   }
};

int n, m, L;
vector < vector <edge> > Adj;
long long damage[M], actualCost; //damage[k] = sum(d[i][j]) when edge with idx = k is removed
int dist[N], Par[N];

void dijkstra(int src, int banIdx, int d[], int Pi[]) {
   bool vis[N];
   for (int i = 0; i < n; ++i)
      vis[i] = false, d[i] = infi, Pi[i] = -1;

   d[src] = 0;
   priority_queue <pii, vector <pii>, greater <pii> > Q;
   Q.push(pii(d[src], src));

   while (!Q.empty()) {
      pii tmp = Q.top();
      Q.pop();
      int u = tmp.y;
      if (vis[u]) continue;
      vis[u] = true;

      for (edge E : Adj[u]) {
         int v = E.v, w = E.w, id = E.id;
         if (banIdx == id) continue;

         if (!vis[v] && d[u] < infi && d[v] > d[u] + w) {
            d[v] = d[u] + w;
            Pi[v] = id;
            Q.push(pii(d[v], v));
         }
      }
   }

}

void solve() {
   for (int i = 0; i < m; ++i)
      damage[i] = 0;

   actualCost = 0;
   for (int i = 0; i < n; ++i) {

      dijkstra(i, -1, dist, Par);

      long long sumOverj = 0;
      for (int j = 0; j < n; ++j) {
         sumOverj += (dist[j] == infi ? L : dist[j]);
      }
      actualCost += sumOverj;

      bool inSpanTree[M];
      for (int k = 0; k < m; ++k)
         inSpanTree[k] = false;

      for (int j = 0; j < n; ++j)
         if (j != i) inSpanTree[Par[j]] = true;

      for (int k = 0; k < m; ++k) { // correction
         if (inSpanTree[k]) { // will run atmost n - 1 time
            dijkstra(i, k, dist, Par);

            long long sumOverjWOk = 0;
            for (int j = 0; j < n; ++j)
               sumOverjWOk += (dist[j] == infi ? L : dist[j]);
            damage[k] += sumOverjWOk;
         }
         else damage[k] += sumOverj;
      }
   }

   long long mx = actualCost;
   for (int i = 0; i < m; ++i) {
      mx = max(mx, damage[i]);
   }

   cout << actualCost << ' ' << mx << '\n';
}

void read() {
   Adj.assign(n, vector <edge> ());

   int u, v, c;
   for (int i = 0; i < m; ++i) {
      cin >> u >> v >> c;
      --u, --v;
      Adj[u].push_back({v, c, i});
      Adj[v].push_back({u, c, i});
   }
}

signed main() {
   while (cin >> n >> m >> L) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}


