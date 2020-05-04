#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = 1010;

int V, E;
vector < vector <pii> > Adj;
vector <int> zeroList;

int vis[N], idx[N], cn;
vector <int> order;
vector < vector <int> > CComp;
vector < vector <pii> > AdjT;
vector < set <int> > AdjCC;

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
	CComp[cn].push_back(u);

	for (auto vPair : AdjT[u]) {
		int v = vPair.x;
		if (!vis[v]) dfsCC(v);
	}
}

void ccomp_dir() {
	cn = 0;
	for (int i = 0; i < N; ++i)
		vis[i] = 0, idx[i] = -1;
	AdjT.assign(V, vector <pii> ());
	order.clear();
	CComp.clear();

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

void gen_Condensed() {
	AdjCC.assign(cn, set <int>()); // the condensed graph (DAG)
	for (int u = 0; u < V; ++u) {
		for (auto vPair : Adj[u]) {
			int v = vPair.x;
			if (idx[u] == idx[v]) continue;
			AdjCC[idx[u]].insert(idx[v]);
		}
	}
}

void solve() {
	ccomp_dir();
	gen_Condensed();
	int in_deg[N], ans = 0;
	for (int i = 0; i < cn; ++i) in_deg[i] = 0;

	for (int u = 0; u < cn; ++u) {
		for (auto v : AdjCC[u]) {
			in_deg[v] += 1;
		}
	}
	for (auto v : zeroList) {
		in_deg[idx[v]] += 1; //somewhat wrong
	}

	for (int i = 0; i < cn; ++i)
		if (in_deg[i] == 0) ++ans;
	cout << ans << '\n';
}

void read_Solve() {
	int n, m, u, v, w = 1;
	while (cin >> n >> m) {
		V = n, E = m;
		Adj.assign(V, vector <pii>());
		zeroList.clear();

		for (int e = 0; e < m; ++e) {
			cin >> u >> v;
			if (u == 0 || v == 0) {
				if (u == 0) zeroList.emplace_back(v - 1);
				continue;
			}
			--u, --v;
			Adj[u].emplace_back(pii(v, w));
		}
		solve();
	}
}


signed main() {
	read_Solve();

	return EXIT_SUCCESS;
}
