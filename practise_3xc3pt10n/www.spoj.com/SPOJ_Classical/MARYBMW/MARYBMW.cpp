/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
 When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows * * * * * * */
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;
using pii = pair <int, long long>;
const int N = (int)1e5 + 10;
const long long inf = (long long)1e18 + 2;

int n, m;
struct Edges {
   int u, v;
   long long w;
   inline bool operator <  (const Edges& o) const {
      return w < o.w;
   }
   inline bool operator >  (const Edges& o) const {
      return w > o.w;
   }
};

vector <long long> wgts;
vector <Edges> edges;
vector < vector <pii> > Adj;
bool vis[N];

void dfs (int u, int t, long long mx) {
   vis[u] = true;

   for (auto vPair : Adj[u]) {
      int v = vPair.x;
      long long w = vPair.y;
      if (!vis[v] && w >= mx) {
         dfs(v, u, mx);
      }
   }
}

void runDFS(long long mx) {
   for (int i = 0; i < n; ++i) vis[i] = false;
   dfs (0, n - 1, mx);
}

void solveTLE() {
   int low = 0, high = (int)wgts.size() - 1, guess;

   runDFS(-inf);
   if (!vis[n - 1]) {
      cout << -1 << '\n';
      return;
   }

   while (low <= high) {
      guess = (low + high)/2;
      for (int i = 0; i < n; ++i) vis[i] = false;
      dfs (0, n - 1, wgts[guess]);

      if (vis[n - 1]) low = guess + 1;
      else high = guess - 1;
   }
   long long ans = wgts[high];

   cout << ans << '\n';
}

void read() {
   cin >> n >> m;
   Adj.assign(n, vector <pii> ());
   edges.clear();
   wgts.clear();

   int u, v;
   long long w;

   for (int i = 0; i < m; ++i) {
      cin >> u >> v >> w;
      if (u == v) continue;
      --u, --v;
      if (u > v) swap(u, v);
      edges.push_back({u, v, w});
   }
   sort(edges.begin(), edges.end(), greater<Edges>());

   for (Edges e : edges) {
      u = e.u, v = e.v;
      w = e.w;
      Adj[u].push_back(pii(v, w));
      Adj[v].push_back(pii(u, w));
      wgts.push_back(w);
   }
   sort (wgts.begin(), wgts.end());
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      read();
      solveTLE();
   }

   return EXIT_SUCCESS;
}


