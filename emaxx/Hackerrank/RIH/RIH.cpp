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

const int N = (int)2e5 + 10;

int n, m;

struct Edge {
   int u, v, w, id;
   inline bool operator < (const Edge &o) const {
      return w < o.w;
   }
   Edge rev () {
      Edge e = {v, u, w, id};
      return e;
   }
};

long long used[N];
vector < vector <Edge> > T;
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

void kruskals () {
   sort (edges.begin(), edges.end());
   makeSet();
   int cnt = 0;

   for (Edge e : edges) {
      int u = e.u, v = e.v;
      if (findSet(u) == findSet(v)) continue;
      mergeSet(u, v);
      MST.push_back(e);
      T[u].push_back(e);
      T[v].push_back(e.rev());
      ++cnt;
   }

   assert (cnt == n - 1);
}

int dfs (int u, int pr, bool vis[]) {
   vis[u] = true;
   int cnt = 1;

   for (Edge e: T[u]) {
      assert(e.u == u);
      int v = e.v, w = e.w, id = e.id;
      if (v == pr) continue;
      if (!vis[v]) {
         used[id] = 1ll * dfs (v, u, vis);
         cnt += (int)used[id];
      }
   }
   return cnt;
}

void solve() {
   kruskals();

   bool vis[N] = {0};
   dfs(0, -1, vis);

   long long val[2 * N] = {0};
   int mx = 0;
   for (Edge e : MST) {
      mx = max(mx, e.w);
      val[e.w] = used[e.id] * (1ll * n - used[e.id]);
   }

   vector <int> ans;
   long long car = 0;
   for (int i = 0; (car != 0 || i <= mx); ++i) {
      val[i] += car;
      if (val[i] % 2) {
         val[i] -= 1;
         ans.push_back(1);
      }
      else ans.push_back(0);
      car = val[i] >> 1;
   }
   reverse(ans.begin(), ans.end());
   for_each(ans.begin(), ans.end(), [](int bin) { cout << bin; });
   cout << '\n';
}

void read() {
   cin >> n >> m;
   T.assign(n, vector <Edge> ());
   fill (used, used + n, 0);
   edges.clear();
   MST.clear();
   int u, v, w;
   for (int i = 0; i < m; ++i) {
      cin >> u >> v >> w;
      --u, --v;
      edges.push_back({u, v, w, i});
   }
}

signed main() {
   read();
   solve();

   return EXIT_SUCCESS;
}

