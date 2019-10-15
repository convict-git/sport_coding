/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
 When I wrote this code,
 only God and I understood what I was doing
 ** * * * * * * * Now, only God knows * * * * * * */

#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
template<class T> inline bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> inline bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;
using pii = pair <int, int>;

struct pili {
	int x;
	long long y;
	int idx;
};

const int N = 1e5 + 10;
vector < vector <pili> > Adj;
int V;
long long memo[2*N + 1], mem, w;
int v, nxtIdx;

long long dfs(int s, int pr, long long wt, int idx) {
	mem = wt;
	for (auto vPair : Adj[s]) {
		v = vPair.x;
		w = vPair.y;
		nxtIdx = vPair.idx;
		if (v == pr) continue;
		if(memo[nxtIdx] != -1) mem = max(mem, memo[nxtIdx] + wt);
		else mem = max(mem, dfs(v, s, w, nxtIdx) + wt);
	}
	return memo[idx] = mem;
}

void solve() {
	vector <long long> Ans(V, 0);
	for (int u = 0; u < V; ++u) {
		for (auto vPair : Adj[u]) {
			v = vPair.x;
			w = vPair.y;
			nxtIdx = vPair.idx;
			if(memo[nxtIdx] != -1) Ans[u] = max(Ans[u], memo[nxtIdx]);
			else Ans[u] = max(Ans[u], dfs(v, u, w, nxtIdx));
		}
	}

	for (auto it : Ans) printf("%lld ", (long long)it);
	printf("\n");
}

void read() {
	for (int i = 0; i < 2*N + 1; ++i) memo[i] = -1;
	int u, v, w;
	scanf (" %i", &V);
	Adj.assign(V, vector <pili>());

	for (int e = 0; e < V - 1; ++e) {
		scanf (" %i %i %i", &u, &v, &w);
		--u, --v;
		Adj[u].push_back({v, w, 2*e});
		Adj[v].push_back({u, w, 2*e + 1});
	}
}

int main() {
	int tc;
	scanf (" %i", &tc);
	while (tc--) {
		read();
		solve();
	}

	return EXIT_SUCCESS;
}
