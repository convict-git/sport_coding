#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;
using plli = pair <long long, int>;

const long long inf = (long long) 1e18;
const int N = 104;
int n, E, T, M, V;
vector < vector <plli> >Adj;
vector <long long> d;

void read() {
	cin >> n >> E >> T >> M;
	--E;
	V = n;
	Adj.resize(N);
	int u, v;
	long long w;
	while (M--) {
		cin >> u >> v >> w;
		--u, --v;
		Adj[v].push_back({w, u});
	}
}

void dijkstra (int src, int tar = -1) {
	priority_queue < plli, vector <plli>, greater <plli> > Q;
	d.resize(V);
	fill (d.begin(), d.end(), inf);
	vector <bool> vis(V, false);
	vector <int> Par(V, -1);

	for (int u = 0; u < V; ++u)
		d[u] = (u == src ? 0 : inf);
	Q.push ({d[src], src});

	while (!Q.empty()) {
		plli minVer = Q.top();
		Q.pop();
		int u = minVer.second;

		if (vis[u] == true) continue;
		else vis[u] = true;
		if (u == tar) break;

		for (auto vertexPair : Adj[u]) {
			int v = vertexPair.second;
			long long w = vertexPair.first;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				Par[v] = u;
				Q.push ({d[v], v});
			}
		}
	}
}

void solve () {
	int ctr = 0;
	for (auto D : d) D <= T ? ++ctr : ctr;
	cout << ctr << '\n';
}

int main() {
	IOS; PREC;
	read();
	dijkstra(E);
	solve();

	return EXIT_SUCCESS;
}
