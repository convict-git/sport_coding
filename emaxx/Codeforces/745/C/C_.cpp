#include         <bits/stdc++.h>
#define x        first
#define y        second
#define bg(x)   "[ " << #x << " : " << x << " ]"
using namespace std;
using pii = pair <int,int>;
const int N = (int)1e3 + 10;

vector <vector <int>> Adj;
int n, m, k;
vector <int> C, govC;
vector <pii> edges;

int dfs (int u, bool vis[]) {
   vis[u] = true;
   int cnt = 0;
   for (int v : Adj[u]) {
      if (!vis[v]) cnt += dfs(v, vis);
   }
   return cnt + 1;
}
inline int nc2(int t) { return (t * (t - 1))/2; }

void solve() {
   int remove = 0;
   for (int i = 0; i < m; ++i) {
      int u = edges[i].x, v = edges[i].y;
      Adj[u].push_back(v);
      Adj[v].push_back(u);
   }

   bool vis[N];
   for (int i = 0; i < k; ++i) {
      fill (vis, vis + n, false);
      govC.push_back(dfs(C[i], vis));
      remove += govC[i];
      //cerr << bg(govC[i]) << '\n';
   }

   remove = n - remove;
   //cerr << bg(remove) << '\n';
   int mx = 0, mxIdx = -1;
   for (int i = 0; i < k; ++i)
      if (mx < govC[i])
         mx = govC[i], mxIdx = i;

   int ans = 0;

   for (int i = 0; i < k; ++i)
      if (i != mxIdx) ans += nc2(govC[i]);

   govC[mxIdx] += remove;
   ans += nc2(govC[mxIdx]);
   cout << ans - m << '\n';
}

void read() {
   cin >> n >> m >> k;
   C.clear();
   Adj.assign(n, vector <int>());
   edges.clear();
   govC.clear();
   int u, v;
   //cerr << bg(n) << ' ' << bg(m) << ' ' << bg(k) << '\n';
   for (int i = 0; i < k; ++i) {
      cin >> u;
      --u;
      C.push_back(u);
   }
   for (int i = 0; i < m; ++i) {
      cin >> u >> v;
      --u, --v;
      edges.push_back(pii(u, v));
   }
}

signed main() {
   read();
   solve();

   return EXIT_SUCCESS;
}

