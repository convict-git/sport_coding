#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (2); cout << fixed
#define bg(x)    "[ " << #x << " : " << x << " ]"
#define x        first
#define y        second
using namespace std;
using ld = long double;

const int N = 105;
const long double eps = 1e-9;

struct Edge {
   int u, v;
   long double w;
   inline bool operator < (const Edge &o) const {
      return w + eps < o.w;
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

long double kruskals () {
   long double cost = 0;
   sort (edges.begin(), edges.end());
   makeSet();
   int cnt = 0;

   for (Edge e : edges) {
      int u = e.u, v = e.v;
      long double w = e.w;
      if (findSet(u) == findSet(v)) continue;
      cost += w;
      mergeSet(u, v);
      ++cnt;
   }

   assert (cnt == n - 1);
   return cost;
}

inline long double wt (const pair <ld, ld> &p1, const pair <ld, ld> &p2) {
   return hypot(p1.x - p2.x, p1.y - p2.y);
}

void solve() {
   long double ans = kruskals();
   cout << ans << '\n';
}

void read() {
   cin >> n;
   edges.clear();
   vector <pair<ld, ld>> points(n, pair <ld, ld>());
   for (int i = 0; i < n; ++i) {
      cin >> points[i].x >> points[i].y;
   }
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
         if (i == j) continue;
         edges.push_back({i, j, wt(points[i], points[j])});
      }
   }
}


signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   for (int i = 0; i < tc; ++i) {
      if (i) cout << '\n';
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

