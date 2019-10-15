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

const int N = (int)1e3 + 10;

int V, E;
vector < vector <pii> > Adj;

int tmr;
int f[N], t[N];
int vis[N] = {0};
set < pair <int, int> > bridges;

void markBridge(int u, int v) {
	++u, ++v;
	if (u < v) bridges.insert({u, v});
	else bridges.insert({v, u});
}

void dfsF (int u, int pr) {
	vis[u] = 1;
	t[u] = f[u] = tmr++;

	for (auto vPair : Adj[u]) {
		int v = vPair.x;
		if (v == pr) continue;
		if (vis[v])
			f[u] = min (f[u], t[v]);
		else {
			dfsF (v, u);
			f[u] = min (f[u], f[v]);
			if (f[v] > t[u])
				markBridge(u, v);
		}
	}
}

void find_bridges() {
	tmr = 0;
	bridges.clear();
	for (int u = 0; u < V; ++u) {
		vis[u] = 0, t[u] = f[u] = -1;
	}

	for (int u = 0; u < V; ++u) {
		if (!vis[u]) {
			dfsF (u, -1);
		}
	}
}

void read() { int n, m, u, v, w;
	cin >> n >> m;
	V = n, E = m;
	Adj.assign(V, vector <pii>());

	for (int e = 0; e < m; ++e) {
		cin >> u >> v;
		--u, --v;
		Adj[u].emplace_back(pii(v, w));
		Adj[v].emplace_back(pii(u, w));
	}
}

void solve(int tc) {
	cout << "Caso #" << tc << '\n';
	if (bridges.size() != 0) {
		cout << bridges.size() << '\n';
		for (auto p : bridges) {
			cout << p.x << ' ' << p.y << '\n';
		}
	}
	else cout << "Sin bloqueos\n";
}

signed main() {
	IOS; PREC;
	int tc;
	cin >> tc;
	string s;
	for (int TC = 1; TC <= tc; ++TC) {
		cin.ignore();
		read();
		find_bridges();
		solve(TC);
	}

	return EXIT_SUCCESS;
}

