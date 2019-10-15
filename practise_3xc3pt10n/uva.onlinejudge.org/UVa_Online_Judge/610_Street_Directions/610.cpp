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
set <pii> edges;

const int N = 1010;

int V, E;
vector < vector <pii> > Adj;

int tmr;
int f[N], t[N];
int vis[N] = {0};
set < pair <int, int> > bridges;

void markBridge(int u, int v) {
	bridges.insert({u, v});
	bridges.insert({v, u});
}

void dfsF (int u, int pr) {
	vis[u] = 1;
	t[u] = f[u] = tmr++;

	for (auto vPair : Adj[u]) {
		int v = vPair.x;
		if (v == pr) continue;
		if (vis[v]) {
			f[u] = min (f[u], t[v]);
            if (t[v] < t[u]) edges.insert ({u, v}); //this was a BUG
            // vis can be of two types, top to down, and down to top (in DFS tree),
            // so was adding both without checking the condition
        }
		else {
			dfsF (v, u);
			f[u] = min (f[u], f[v]);
			if (f[v] > t[u]) {
				markBridge(u, v);
                edges.insert ({u, v});
                edges.insert ({v, u});
            }
            else edges.insert({u, v});
		}
	}
}

void find_bridges() {
	tmr = 0;
	for (int u = 0; u < V; ++u) {
		vis[u] = 0, t[u] = f[u] = -1;
	}

	bridges.clear();
    edges.clear();

	for (int u = 0; u < V; ++u) { // else run for every connected component
		if (!vis[u]) {
			dfsF (u, -1);
		}
	}
}

void read_Solve() {
	int n, m, u, v, w = 1, tc = 1;
	while (cin >> n >> m, n || m) {
        V = n, E = m;
        Adj.assign(V, vector <pii>());

        for (int e = 0; e < m; ++e) {
            cin >> u >> v;
            --u, --v;
            Adj[u].emplace_back(pii(v, w));
            Adj[v].emplace_back(pii(u, w)); // undirected
        }

        find_bridges();
        cout << tc << '\n' << '\n';
        for (auto it : edges)
            cout << it.x + 1 << ' ' << it.y + 1 << '\n';
        cout << "#\n";
        ++tc;
    }
}

signed main() {
    IOS; PREC;
    read_Solve();

	return EXIT_SUCCESS;
}

