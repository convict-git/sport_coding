#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;

const int N = 1004;
const int infi = (int)1e9;
int n, m;
vector <vector <int>> Adj;
int V;

void bfs (int src, int dest = -1) {
	vector <bool> used(V, false);
	vector <int> dist(V, infi), Par(V, -1);
	queue <int> Q;

	used[src] = true;
	dist[src] = 0;

	Q.push(src);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		if (dest != -1 && u == dest) break;
		for (auto v : Adj[u]) {
			if (!used[v] && Adj[v].size() > 2) {
				used[v] = true;
				Q.push(v);
				dist[v] = dist[u] + 1;
				Par[v] = u;
			}
		}
	}
	if (dist[dest] == infi) printf("Poor Koorosh\n");
	else printf("%d\n", dist[dest]);
}

void solve() {
	vector <int> OddVert;
	for (int u = 0; u < V; ++u) {
		if (Adj[u].size() & 1) OddVert.push_back(u);
	}
	assert (OddVert.size() == 2 || OddVert.size() == 0);

	bool ok = true;
	for (int v = 0; v < V; ++v) {
		if (Adj[v].size() < 2) {
			ok = false;
		break;
		}
	}

	if (!ok) printf("Poor Koorosh\n");
	else if (OddVert.size() == 0) {
		printf("0\n");
	}
	else {
		if (Adj[OddVert[0]].size() == 1) printf("Poor Koorosh\n");
		else bfs(OddVert[0], OddVert[1]);
	}
}

int main() {

	while (scanf("%d %d", &n, &m), (n || m)) {
		Adj.assign(n, vector <int>());
		V = n;
		int u, v;
		while (m--) {
			scanf ("%d %d", &u, &v);
			--u, --v;
			Adj[u].push_back(v);
			Adj[v].push_back(u);
		}
		solve();
	}

	return EXIT_SUCCESS;
}
