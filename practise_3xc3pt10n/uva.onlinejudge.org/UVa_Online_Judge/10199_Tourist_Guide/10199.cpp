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

const int N = 105;
map <string, int> mp;
map <int, string> mps;

int V, E;
vector < vector <pii> > Adj;

int f[N], t[N], vis[N], treeDeg[N];
int tmr;
set <int> cutVertex;

void markCutVertex (int u) {
	cutVertex.insert(u);
}

void dfsF (int u, int pr) {
	vis[u] = 1;
	f[u] = t[u] = tmr++;

	for (auto vPair : Adj[u]) {
		int v = vPair.x;
		if (v == pr) continue;
		if (vis[v])
			f[u] = min(f[u], t[v]);
		else {
			dfsF (v, u);
			f[u] = min(f[u], f[v]);

			if (f[v] >= t[u] && pr != -1) //careful : u shouldn't be root here
				markCutVertex(u);

			++treeDeg[u];
		}
		if (pr == -1 && treeDeg[u] > 1) // case of u is root
			markCutVertex(u);
	}
}

void find_cut_vertex() {
	tmr = 0;
	cutVertex.clear();
	for (int u = 0; u < V; ++u) {
		vis[u] = treeDeg[u] = 0;
		f[u] = t[u] = -1;
	}

	for (int u = 0; u < V; ++u)
		if (!vis[u]) dfsF (u, -1);
}

void read_Solve() {
	int n, m, u, v;
	string su, sv;
	int w = 1;
	int tc = 1;
	while (true) {
		cin >> n;
		if (n == 0) break;
		if (tc != 1) cout << '\n';
		for (int i = 0; i < n; ++i) {
			cin >> su;
			mp[su] = i;
			mps[i] = su;
		}

		cin >> m;
		V = n, E = m;
		Adj.assign(V, vector <pii>());

		for (int e = 0; e < m; ++e) {
			cin >> su >> sv;
			u = mp[su], v = mp[sv];
			Adj[u].emplace_back(pii(v, w));
			Adj[v].emplace_back(pii(u, w)); // undirected
		}
		find_cut_vertex();
		cout << "City map #" << tc << ':' << ' ' << cutVertex.size() << " camera(s) found\n";
		set <string> cities;
		for (auto u_ : cutVertex)
			cities.insert(mps[u_]);
		for (auto u_ : cities)
			cout << u_ << '\n';
		++tc;
	}
}

signed main() {
	IOS; PREC;
	read_Solve();

	return EXIT_SUCCESS;
}

