#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;

const int N = (int) 1e5 + 10;
const int infi = (int)1e9;

int dr[N], ds[N], Par[N];
int n, m, sr, f, r;
vector <vector <int> > Adj;

int bfs (int s, int t, int flag, int d[]) {
	bool vis[n];
	queue <int> q;
	fill (d, d + n, infi);
	fill (vis, vis + n, false);
	fill (Par, Par + n, -1);

	vis[s] = true;
	d[s] = 0;
	q.push(s);

	vector <int> pq;
	while (!q.empty()) {
		int u = q.front();
		q.pop();

		pq.clear();
		for (auto v : Adj[u])
			if (!vis[v]) pq.push_back(v);
		sort (pq.begin(), pq.end(),
				[&] (const int p1, const int p2)->bool
				{return dr[p1] > dr[p2];});

		for (auto v : pq) {
			d[v] = d[u] + 1;
			vis[v] = true;
			Par[v] = u;
			q.push(v);
		}
	}

	if (flag) {
		int mn = infi;
		for (int i = t; i != -1; i = Par[i])
			mn = min(mn, dr[i]);
		return mn;
	}
	else return infi;
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
}

void solve() {
	bfs (r, f, false, dr);
	int ans = bfs(sr, f, true, ds);
	cout << ans << '\n';
}

int main() {
	read();
	solve();
	return EXIT_SUCCESS;
}

