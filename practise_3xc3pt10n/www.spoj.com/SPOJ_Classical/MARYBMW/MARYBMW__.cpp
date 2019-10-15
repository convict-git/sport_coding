#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;
using pii = pair <int, long long>;

const int N = (int)1e5 + 10;
const long long inf = (long long)1e18 + 10;
struct Edge {
   int u, v;
   long long w;
   inline bool operator > (const Edge &o) const {
      return w > o.w;
   }
};

vector <Edge> edges;
vector <vector <pii>> T;

int n, m;
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
   makeSet();
   long long ans = inf;
   bool ok = false;

   for (Edge e : edges) {
      int u = e.u, v = e.v;
      long long w = e.w;
      if (findSet(u) == findSet(v)) continue;
      mergeSet(u, v);
      if (!ok && findSet(0) == findSet(n - 1)) {
         ans = min(ans, w);
         ok = true;
      }
      T[u].push_back(pii(v, w));
      T[v].push_back(pii(u, w));
   }
   return ans;
}

// bool dfs (int u, int pr, int tar, long long& mn, bool vis[]) {
//    vis[u] = true;
//    for (auto vPair : T[u]) {
//       int v = vPair.x;
//       long long w = vPair.y;
//       if (v == pr) continue;
//       if (v == tar) {
//          vis[tar] = true;
//          mn = min(mn, w);
//          return true;
//       }
//       if (!vis[v]) {
//          bool ok = dfs (v, u, tar, mn, vis);
//          if (ok) {
//             mn = min(mn, w);
//             return true;
//          }
//       }
//    }
//    return false;
// }

void solve() {
   sort (edges.begin(), edges.end(), greater<Edge>());
   long long ans = kruskals();
   cout << (ans == inf ? -1 : ans) << '\n';
//    long long mn = inf;
//    bool vis[N];
//    for (int i = 0; i < n; ++i) vis[i] = false;
//
//    bool ok = dfs (0, -1, n - 1, mn, vis);
//    cout << (ok ? mn : -1) << '\n';
}

void read() {
   cin >> n >> m;
   T.assign(n, vector <pii>());
   edges.clear();
   int u, v;
   long long w;
   for (int i = 0; i < m; ++i) {
      cin >> u >> v >> w;
      --u, --v;
      edges.push_back({u, v, w});
   }
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   for (int i = 1; i <= tc; ++i) {
      read();
      solve();
   }
   return EXIT_SUCCESS;
}

