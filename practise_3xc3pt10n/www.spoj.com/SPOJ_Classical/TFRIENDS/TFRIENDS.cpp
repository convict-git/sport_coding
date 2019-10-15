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

const int N = 110;
int V, n;
vector < vector <pii> > Adj;

int vis[N], cn;
vector <int> order;
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
			dfsCC (u);
			++cn;
		}
	}
}

void read() {
	cin >> n;
	V = n;
	Adj.assign(n, vector <pii>());
	string s;
	for (int u = 0; u < n; ++u) {
		cin >> s;
		for (int v = 0; v < n; ++v) {
			if (s[v] == 'Y') {
				Adj[u].push_back(pii(v, 1));
			}
		}
	}
}

signed main() {
	IOS; PREC;
	int tc;
	cin >> tc;
	while (tc--) {
		read();
		ccomp_dir();
		cout << cn << '\n';
	}
	return EXIT_SUCCESS;
}

