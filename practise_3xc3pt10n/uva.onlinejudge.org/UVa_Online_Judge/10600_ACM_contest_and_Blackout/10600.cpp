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

const int N = 105;

struct Edge {
   int u, v;
   int w;
   inline bool operator < (const Edge &o) const {
      return w < o.w;
   }
};

int n, m;
vector <Edge> edges;
int rep[N], rnk[N];
vector <Edge> MST;
int cost = 0;

void makeSet() {
   for(int i = 0; i < n; ++i)
      rep[i] = i, rnk[i] = 0;
}

int findSet(int u) {
   int ru = u;
   while (ru != rep[ru])
      ru = rep[ru];

   while (u != rep[u]) {
      int tmp = rep[u];
      rep[u] = ru;
      u = tmp;
   }
   return ru;
}

void mergeSet(int u, int v) {
   int ru = findSet(u), rv = findSet(v);
   if (rnk[ru] > rnk[rv]) rep[rv] = rep[ru];
   else rep[ru] = rep[rv];

   if (rnk[ru] == rnk[rv])
      ++rnk[rv];
}

int kruskals (Edge ban, bool ok) {
   int total = 0;
   makeSet();
   int cnt = 0;

   for (Edge e : edges) {
      int u = e.u, v = e.v, w = e.w;
      if (!ok && ban.u == e.u && ban.v == e.v) continue;

      if (findSet(u) == findSet(v)) continue;
      total += w;
      mergeSet(u, v);
      ++cnt;
      if (ok) MST.push_back(e);
   }
   return (cnt == n - 1 ? total : INT_MAX);
}

void solve() {
   sort (edges.begin(), edges.end());
   int ans = kruskals({-1, -1, -1}, true);
   int mndiff = INT_MAX;

   for (Edge e : MST) {
      mndiff = min(mndiff, kruskals(e, false));
   }
   cout << ans << ' ' << mndiff << '\n';
}

void read() {
   cin >> n >> m;
   MST.clear();
   edges.clear();
   cost = 0;
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
   while (tc--) { read(); solve(); }

   return EXIT_SUCCESS;
}

