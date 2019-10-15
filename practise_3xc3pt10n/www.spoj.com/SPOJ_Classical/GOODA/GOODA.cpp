#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = (int)1e6 + 10;
vector < vector <pii> > Adj;
int V, E, startv, endv;

int vis[N], cn;
vector <int> order;
vector < vector <pii> > AdjT;
vector < set <int> > AdjCC;
int f[N], idx[N];
long long g[N], dp[N];

void dfsTimer (int u) {
	vis[u] = 1;

	for (auto vPair : Adj[u]) {
		int v = vPair.x;
		if (!vis[v]) dfsTimer (v);
	}
	order.push_back(u);
}

void dfsCC(int u) {
	vis[u] = 1;
	idx[u] = cn;
	g[cn] += 1ll*f[u];

	for (auto vPair : AdjT[u]) {
		int v = vPair.x;
		if (!vis[v]) dfsCC(v);
	}
}

void ccomp_dir() {
	cn = 0;
	AdjT.assign(V, vector <pii> ());
	order.clear();
	fill (vis, vis + N, 0);
	fill (idx, idx + N, -1);

	for (int u = 0; u < V; ++u)
		if (!vis[u]) dfsTimer(u);

	for (int u = 0; u < V; ++u) {
		for (auto vPair : Adj[u]) {
			int v = vPair.x;
			long long w = vPair.y;
			AdjT[v].push_back(pii(u, w));
		}
	}

	fill (vis, vis + N, 0);
	reverse (order.begin(), order.end());

	for (auto u : order) {
		if (!vis[u]) {
			dfsCC (u);
			++cn;
		}
	}
}

void read() {
	int n, m, u, v, w = 1;
	cin >> n >> m >> startv >> endv;
	--startv, --endv;
	V = n, E = m;
	Adj.assign(V, vector <pii>());
	for (int i = 0; i < n; ++i) cin >> f[i];

	for (int e = 0; e < m; ++e) {
		cin >> u >> v;
		--u, --v;
		Adj[u].emplace_back(pii(v, w));
	}
}

vector <int> cc_order;
void dfs_order(int u) {
   vis[u] = true;
   for (int v : AdjCC[u]) if (!vis[v]) dfs_order(v);
   cc_order.push_back(u);
}

void solve() {
	for (int i = 0; i < N; ++i) { // for each connected component
		g[i] = dp[i] = 0;
	}
	ccomp_dir();

	AdjCC.assign(cn, set <int>());
	for (int u = 0; u < V; ++u) {
		for (auto vPair : Adj[u]) {
			int v = vPair.x;
			if (idx[u] == idx[v]) continue;
			AdjCC[idx[u]].insert(idx[v]); // condensed graph's adj
		}
	}

	int src = idx[startv], tar = idx[endv];

	for (int i = 0; i < cn; ++i)
      dp[i] = -1, vis[i] = false;

   for (int i = 0; i < cn; ++i) if (!vis[i]) dfs_order(i);
   reverse(cc_order.begin(), cc_order.end());
   dp[src] = g[src];

   for (int u : cc_order) { // longest path dp on condensed graph
      for (int v : AdjCC[u]) {
         if (dp[u] != -1) dp[v] = max(dp[v], dp[u] + g[v]);
      }
   }

	cout << dp[tar] << '\n';
}

signed main() {
	IOS; PREC;
	read();
	solve();

	return EXIT_SUCCESS;
}
