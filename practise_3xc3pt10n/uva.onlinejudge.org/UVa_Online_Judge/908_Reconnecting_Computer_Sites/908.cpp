#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;

const int N = (int)1e6 + 10;

struct Edge {
   int u, v;
   long long w;
   inline bool operator < (const Edge &o) const {
      return w < o.w;
   }
};

vector <Edge> edges;
int rep[N], rnk[N];

int n, m;

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

long long kruskals () {
   long long cost = 0;
   sort (edges.begin(), edges.end());
   makeSet();
   int cnt = 0;

   for (Edge e : edges) {
      int u = e.u, v = e.v;
      long long w = e.w;
      if (findSet(u) == findSet(v)) continue;
      cost += w;
      mergeSet(u, v);
      ++cnt;
   }

   assert (cnt == n - 1);
   return cost;
}

void solve() {
   cout << kruskals() << '\n';
}

void read() {
   int u, v, w, k;
   long long orig = 0;
   edges.clear();
   for (int i = 0; i < n - 1; ++i) {
      cin >> u >> v >> w;
      orig += w;
   }
   cin >> k;
   for (int i = 0; i < k; ++i) {
      cin >> u >> v >> w;
      --u, --v;
      edges.push_back({u, v, 1ll * w});
   }
   cin >> m;
   for (int i = 0; i < m; ++i) {
      cin >> u >> v >> w;
      --u, --v;
      edges.push_back({u, v, 1ll * w});
   }
   cout << orig << '\n';
}

signed main() {
   IOS; PREC;
   int it = 0;
   while(cin >> n) {
      if (it++) cout << '\n';
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

