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

const int N = 1010;
int V, E;
vector < vector <pii> > Adj;

int nidx = 0;
map <string, int> idx;
map <int, string> st;
set <string> names;

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
int getIdx (string s) {
	if (names.find(s) == names.end()) {
		names.insert(s);
		idx[s] = nidx;
		st[nidx] = s;
		++nidx;
	}
	return idx[s];
}

void read_Solve() {
	int n, m, u, v, w = 1;
	while (cin >> n >> m, n || m) {
		V = n, E = m;
		nidx = 0;
		names.clear();
		idx.clear();
		st.clear();
		Adj.assign(n, vector <pii>());

		string sf, sl;
		for (int i = 0; i < n; ++i) {
			cin >> sf >> sl;
			getIdx(sf + sl);
		}

		for (int e = 0; e < m; ++e) {
			cin >> sf >> sl;
			u = idx[(sf + sl)];
			cin >> sf >> sl;
			v = idx[(sf + sl)];
			Adj[u].emplace_back(pii(v, w));
		}

		ccomp_dir();
		cout << cn << '\n';
	}

}

signed main() {
	IOS; PREC;
	read_Solve();

	return EXIT_SUCCESS;
}

