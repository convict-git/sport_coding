#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;

const int N = (int)1e5 + 10;
const int infi = (int)1e9;

int dr[N], ds[N];
int n, m, sr, f, r;
vector < vector <int> > Adj;

int bfs(int s, int t, int mid, int bs, int d[]) {
	bool vis[N];
	queue <int> q;

	fill (d, d + N, infi);
	fill (vis, vis + N, false);
	d[s] = 0, vis[s] = true;
	if (bs && dr[s] <= mid) return d[t];
	q.push(s);

	while (not q.empty()) {
		int u = q.front();
		q.pop();

		for (auto v : Adj[u]) {
			if (bs && dr[v] <= mid) continue;
			if (!vis[v]) {
				d[v] = d[u] + 1;
				vis[v] = true;
				q.push(v);
			}
		}
	}
	return d[t];
}

void read() {
	cin >> n >> m;
	Adj.assign(n, vector <int>());
	int u, v;
	for (int e = 0; e < m; ++e) {
		cin >> u >> v;
		--u, --v;
		Adj[u].push_back(v);
		Adj[v].push_back(u);
	}
	cin >> sr >> f >> r;
	--sr, --f, --r;
	fill (dr, dr + N, infi);
	fill (ds, ds + N, infi);
}

void solve() {
	bfs(sr, f, 0, 0, ds);
	bfs(r, f, 0, 0, dr);
	int len = ds[f];
	int l = 0, h = n, mid;
	while (l <= h) {
		mid = (l + h)/2;
		if (bfs(sr, f, mid, 1, ds) == len)
			l = mid + 1;
		else h = mid - 1;
	}
	cout << l << '\n';
}

signed main() {
	read();
	solve();
	return EXIT_SUCCESS;
}

