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

const int N = 505;
int n, m;

struct Edge {
   int u, v;
   int w;
   inline bool operator < (const Edge &o) const {
      return w < o.w;
   }
};

vector <Edge> edges;
vector <int> ver;
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

int kruskals () {
   int cost = 0;
   sort (edges.begin(), edges.end());
   makeSet();
   int cnt = 0;

   for (Edge e : edges) {
      int u = e.u, v = e.v;
      int w = e.w;
      if (findSet(u) == findSet(v)) continue;
      cost += w;
      mergeSet(u, v);
      ++cnt;
   }

   assert (cnt == n - 1);
   return cost;
}

inline int wt(int u, int v) {
   int w = 0;
   int mod = 10;
   for (int i = 0; i < 4; ++i) {
      int p = u % mod, q = v % mod;
      u /= 10, v /= 10;
      w += min((q - p + 10) % 10, (p - q + 10) % 10);
   }
   return w;
}

void solve() {
   int ans = kruskals();
   int mn = INT_MAX;
   for (int i = 0; i < n; ++i) {
      mn = min (mn, wt(0, ver[i]));
   }

   ans += mn;
   cout << ans << '\n';
}
void read() {
   edges.clear();
   ver.clear();
   cin >> n;
   ver.assign(n, 0);

   for (int i = 0; i < n; ++i) {
      cin >> ver[i];
   }
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
         if (i == j) continue;
         edges.push_back({i, j, wt(ver[i], ver[j])});
      }
   }
}

signed main() {
   int tc;
   cin >> tc;
   while (tc--) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

