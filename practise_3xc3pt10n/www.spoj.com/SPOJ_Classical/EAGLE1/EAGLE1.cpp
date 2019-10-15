/*
f[v] is length of max path from v in it's subtree (just excluding parent) [ tree is rooted at 0 ]
g[v] is length of max path from v using it's parent [ tree is rooted at 0 ]
dp[v] = max(f[v], g[v]), length of max path from v [when tree is rooted at 'v']
pref[v][i] = length of max path from v in it's subtree (just excluding parent) using 0, ..., i vertices
				in it's adjecency list
suff[v][i] = length of max path from v in it's subtree (just excluding parent) using i, ..., deg[v] - 1 vertices
				in it's adjecency list
*/
/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows * * * * * * */

#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;
using pii = pair <int, long long>;

const int N = (int) 1e5 + 10;
int V, n;
vector < vector <pii> > Adj;
long long f[N], g[N], dp[N];
vector < vector <long long> > pref, suff;

void read() {
	cin >> n;
	V = n;
	Adj.assign(n, vector <pii>());
	pref.assign(n, vector <long long>());
	suff.assign(n, vector <long long>());
	int u, v;
	long long w;
	for (int e = 0; e < n - 1; ++e) {
		cin >> u >> v >> w;
		--u, --v;
		Adj[u].emplace_back(pii(v, w));
		Adj[v].emplace_back(pii(u, w));
	}

	for (int i = 0; i < n; ++i) {
		dp[i] = g[i] = f[i] = 0;
	}
}

void rootAt (int u, int pr) {
	for (int i = 0; i < (int) Adj[u].size(); ++i) {
		int v = Adj[u][i].x;
		if (v == pr)
			Adj[u].erase (Adj[u].begin() + i);
	}

	for (int i = 0; i < (int) Adj[u].size(); ++i) {
		int v = Adj[u][i].x;
		rootAt(v, u);
	}
}

void dfsF (int u) {
	for (auto vPair : Adj[u]) {
		int v = vPair.x;
		dfsF (v);
	}

	long long fval = 0;
	for (auto vPair : Adj[u]) {
		int v = vPair.x;
		long long w = vPair.y;
		fval = max(fval, f[v] + w);
	}
	f[u] = fval;

	int sz = (int) Adj[u].size();
	if (sz != 0) {
		pref[u].assign(sz, 0);
		suff[u].assign(sz, 0);

		for (int i = 0; i < sz; ++i) {
			int v = Adj[u][i].x;
			long long w = Adj[u][i].y;
			if (i == 0) pref[u][i] = f[v] + w;
			else pref[u][i] = max(pref[u][i - 1], f[v] + w);
		}

		for (int i = sz - 1; i >= 0; --i) {
			int v = Adj[u][i].x;
			long long w = Adj[u][i].y;
			if (i == sz - 1) suff[u][i] = f[v] + w;
			else suff[u][i] = max(suff[u][i + 1], f[v] + w);
		}
	}
}

void dfsG (int u, int pr) {
	if (pr == -1) g[u] = 0;
	int sz = (int) Adj[u].size();

	for (int i = 0; i < sz; ++i) {
		long long gval = 0;
		int v = Adj[u][i].x;
		long long w = Adj[u][i].y;
		if (i != 0) {
			gval = max (gval, pref[u][i - 1] + w);
		}
		if (i != sz - 1) {
			gval = max (gval, suff[u][i + 1] + w);
		}
		gval = max (gval, g[u] + w);
		g[v] = gval;
	}

	dp[u] = max (f[u], g[u]);

	for (auto vPair : Adj[u]) {
		int v = vPair.x;
		dfsG (v, u);
	}
}

void solve () {
	for (int v = 0; v < n; ++v) cout << dp[v] << ' ';
	cout << '\n';
}

signed main() {
	IOS; PREC;
	int tc;
	cin >> tc;
	while (tc--) {
		read();
		rootAt(0, -1);
		dfsF(0);
		dfsG(0, -1);
		solve();
	}

	return EXIT_SUCCESS;
}

