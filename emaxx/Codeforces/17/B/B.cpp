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

const int N = 1005;
int n, m;

struct Edge {
   int u, v;
   int w;
   inline bool operator < (const Edge &o) const {
      return v < o.v || (v == o.v && w < o.w);
   }
};

vector <Edge> edges;

void solve() {
   sort(edges.begin(), edges.end());
   int v, w;
   bool vis[N] = {0};
   int totalCost = 0, cnt = 0;
   for (Edge e : edges) {
      v = e.v, w = e.w;
      if (vis[v]) continue;
      totalCost += w;
      vis[v] = true;
      ++cnt;
   }
   cout << (cnt == n - 1 ? totalCost : -1) << '\n';
}

void read() {
   edges.clear();
   cin >> n;
   int q[N];
   for (int i = 0; i < n; ++i) cin >> q[i];

   cin >> m;
   int u, v, w;
   for (int i = 0; i < m; ++i) {
      cin >> u >> v >> w;
      --u, --v;
      edges.push_back({u, v, w});
   }
}

signed main() {
   read();
   solve();

   return EXIT_SUCCESS;
}
