#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = 30;

int V, E, nidx;
vector < vector <pii> > Adj;
map <string, int> idx;
map <int, string> st;
set <string> names;

int vis[N], cn;
vector <int> order;
vector < vector <int> > CComp;
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
	CComp[cn].push_back(u);

	for (auto vPair : AdjT[u]) {
		int v = vPair.x;
		if (!vis[v]) dfsCC(v);
	}
}

void ccomp_dir() {
	cn = 0;
	AdjT.assign(V, vector <pii> ());
	order.clear();
	CComp.clear();
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
			CComp.push_back(vector <int> ());
			dfsCC (u);
			++cn;
		}
	}
}

int getIdx (string s) {
	if (names.find(s) == names.end()) {
		names.insert(s);
		idx[s] = nidx;
		st[nidx] = s; ++nidx;
	}
	return idx[s];
}

void read_Solve() {
	int n, m, u, v, w = 1, tc = 1;

	while (cin >> n >> m, n || m) {
		if (tc != 1) cout << '\n';
		V = n, E = m, nidx = 0;
		idx.clear();
		st.clear();
		names.clear();
		Adj.assign(V, vector <pii>());

		string s1, s2;
		for (int e = 0; e < m; ++e) {
			cin >> s1 >> s2;
			u = getIdx(s1), v = getIdx(s2);
			Adj[u].emplace_back(pii(v, w));
		}

		ccomp_dir();
		cout << "Calling circles for data set " << tc++ << ":\n";
		for (auto cv : CComp) {
			for (int i = 0; i < (int)cv.size(); ++i) {
				cout << st[cv[i]];
				if (i != (int)cv.size() - 1) cout << ", ";
			}
			cout << '\n';
		}
	}
}

signed main() {
	read_Solve();

	return EXIT_SUCCESS;
}
