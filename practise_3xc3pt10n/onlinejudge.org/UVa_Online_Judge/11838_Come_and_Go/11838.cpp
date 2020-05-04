#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;
const int N = (int)2e3 + 10;

int V, E;
vector < vector <pii> > Adj;

int vis[N], cn;
vector <int> order;
vector < vector <int> > CComp;
vector < vector <pii> > AdjT;

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
	CComp[cn].push_back(u);

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
			CComp.push_back(vector <int> ());
			dfsCC (u);
			++cn;
		}
	}
}
void read_solve() {
	int n, m, u, v, P, w = 1;
	while (cin >> n >> m, n || m) {
		V = n, E = m;
		Adj.assign(V, vector <pii>());

		for (int e = 0; e < m; ++e) {
			cin >> u >> v >> P;
			--u, --v;
			Adj[u].emplace_back(pii(v, w));
			if (P == 2) Adj[v].emplace_back(pii(u, w));
		}
		ccomp_dir();
		cout << (cn == 1 ? 1 : 0) << '\n';
	}
}

signed main() {
	read_solve();

	return EXIT_SUCCESS;
}

