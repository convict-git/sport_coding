#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = 3006;
const int infi = (int)1e9;
struct Edge {
   int u, v, w;
   inline bool operator < (const Edge &o) const {
      return w < o.w;
   }
};
vector <Edge> edges;
vector <vector <pii>> T;

int n, m, q;
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

void kruskals () {
   makeSet();

   for (Edge e : edges) {
      int u = e.u, v = e.v;
      long long w = e.w;
      if (findSet(u) == findSet(v)) continue;
      mergeSet(u, v);
      T[u].push_back(pii(v, w));
      T[v].push_back(pii(u, w));
   }
}

int vis[N];
bool dfs (int u, int pr, int tar, int& mx) {
   vis[u] = true;
   for (auto vPair : T[u]) {
      int v = vPair.x, w = vPair.y;
      if (v == pr) continue;
      if (v == tar) {
         vis[tar] = true;
         mx = max(mx, w);
         return true;
      }
      if (!vis[v]) {
         bool ok = dfs (v, u, tar, mx);
         if (ok) {
            mx = max(mx, w);
            return true;
         }
      }
   }
   return false;
}

void dfsi (int u, int pr) {
   vis[u] = true;
   for (auto vPair : T[u]) {
      int v = vPair.x, w = vPair.y;
      if (v == pr) continue;
      if (!vis[v]) dfsi (v, u);
   }
}

void solve(int tc) {
   sort (edges.begin(), edges.end());
   kruskals();
   cin >> q;
   int k, t;

   cout << "Case " << tc << '\n';
   while (q--) {
      cin >> k >> t;
      --k, --t;
      for (int i = 0; i < n; ++i)
         vis[i] = false;
      int mx = -infi;
      bool ok = dfs (k, -1, t, mx);
      //assert(ok);
      cout << mx << '\n';
   }
   cout << '\n';
}

void read() {
   cin >> n >> m;
   T.assign(n, vector <pii>());
   edges.clear();
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
   for (int i = 1; i <= tc; ++i) {
      read();
      solve(i);
   }
   return EXIT_SUCCESS;
}

