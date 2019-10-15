#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;

const int N = 1e5 + 10;

int V, E;
vector < vector <pii> > Adj;

void read() {
	int n, m, u, v;
	long long w;
	cin >> n >> m;
	V = n, E = m;
	Adj.assign(V, vector <pii>());

	for (int e = 0; e < m; ++e) {
		cin >> u >> v >> w;
		--u, --v;
		Adj[u].emplace_back(pii(v, w));
		// Adj[v].emplace_back(pii(u, w)); // undirected
	}
}
signed main() {

	return EXIT_SUCCESS;
}

