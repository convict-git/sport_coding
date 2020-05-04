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
const int N = (int)1e4 + 10;
int n, m;

struct Edge {
   int u, v;
   long long w;
   bool inMST;
   inline bool operator < (const Edge &o) const {
      return w < o.w;
   }
};

vector <Edge> edges;
vector <Edge> MST;
int rep[N], rnk[N];

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

   for (Edge &e : edges) {
      int u = e.u, v = e.v;
      long long w = e.w;
      if (findSet(u) == findSet(v)) continue;
      cost += w;
      e.inMST = true;
      mergeSet(u, v);
      MST.push_back(e);
      ++cnt;
   }

   //assert (cnt == n - 1);
   return cost;
}

void solve() {
   kruskals();
   if ((int)MST.size() == m) cout << "forest\n";
   else {
      for (int i = 0, j = 0; i < m; ++i) {
         if (edges[i].inMST) continue;
         if (j != 0) cout << ' ';
         ++j;
         cout << edges[i].w;
      }
      cout << '\n';
   }
}

void read() {
   int u, v, w;
   MST.clear();
   edges.clear();
   for (int i = 0; i < m; ++i) {
      cin >> u >> v >> w;
      edges.push_back({u, v, 1ll*w, false});
   }
}

signed main() {
   while (cin >> n >> m, n || m) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

