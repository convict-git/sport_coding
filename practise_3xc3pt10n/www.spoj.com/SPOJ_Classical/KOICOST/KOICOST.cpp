#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;
using ll = long long;

const int N = (int)1e6 + 10;
const int M = (int)1e6 + 10;
const int infi = (int)1e9;

struct Edge {
   int u, v;
   ll w;
   inline bool operator > (const Edge &o) const {
      return w > o.w;
   }
};

int n, m;
int rep[N], rnk[N], sz[N];
vector <Edge> edges;
ll cum[M];

template <typename T> T add(const T& a, const T& b) {
   return (a + b) % infi;
}
template <typename T> T mul(const T& a, const T& b) {
   return (a * b) % infi;
}

void makeSet() {
   for(int i = 0; i < n; ++i)
      rep[i] = i, rnk[i] = 0, sz[i] =  1;
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
   if (rnk[ru] > rnk[rv]) {
      rep[rv] = rep[ru];
      sz[ru] += sz[rv];
   }
   else {
      rep[ru] = rep[rv];
      sz[rv] += sz[ru];
   }

   if (rnk[ru] == rnk[rv]) {
      ++rnk[rv];
   }
}

void solve() {
   ll ans = 0;
   sort (edges.begin(), edges.end(), greater <Edge>());

   for (int i = m - 1; i >= 0; --i) {
      if (i == m - 1) cum[i] = edges[i].w;
      else cum[i] = add <ll> (cum[i + 1], edges[i].w);
   }

   makeSet();

   for (int i = 0; i < m; ++i) {
      Edge e = edges[i];
      int u = e.u, v = e.v;
      int ru = findSet(u), rv = findSet(v);
      if (ru == rv) continue;

      ans = add <ll> (ans, mul<ll>((1ll* sz[ru] * sz[rv]), cum[i]));
      mergeSet(u, v);
   }
   cout << ans << '\n';
}

void read() {
   edges.clear();
   for (int i = 0; i < m; ++i) cum[i] = 0;
   int u, v, w;
   for (int i = 0; i < m; ++i) {
      cin >> u >> v >> w;
      --u, --v;
      if (u > v) swap(u, v);
      edges.push_back({u, v, 1ll*w});
   }
   assert ((int)edges.size() == m);
}

signed main() {
   while (cin >> n >> m) {
      read(); solve();
   }

   return EXIT_SUCCESS;
}

