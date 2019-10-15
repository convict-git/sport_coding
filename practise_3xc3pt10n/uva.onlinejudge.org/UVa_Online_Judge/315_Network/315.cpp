#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = 105;

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
void solve() {
	find_cut_vertex();
	cout << cutVertex.size() << '\n';
}

void read() {
	int n, u, v;
	string s;
	int tc = 0;

	while (getline(cin, s)) {
		stringstream ss(s);
		if (tc == 0) {
			ss >> n;
			V = n;
			if (n == 0) break;
			Adj.assign(n, vector <pii>());
			tc = 1;
			continue;
		}
		ss >> u;
		if (u == 0) {
			tc = 0;
			solve();
			Adj.clear();
			continue;
		}
		--u;
		while (ss >> v) {
			--v;
			Adj[u].push_back(pii(v, 1));
			Adj[v].push_back(pii(u, 1));
		}
	}
}

signed main() {
	read();

	return EXIT_SUCCESS;
}

