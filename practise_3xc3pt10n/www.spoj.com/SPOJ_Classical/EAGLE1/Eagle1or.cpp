#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include         <bits/stdc++.h>

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;
//using pili = pair <int, long long>;
using pii = pair <int, int>;

struct pili {
	int x;
	long long y;
	int idx;
};

/* struct HASH{
    size_t operator()(const pair<int,int>&x)const{
        return hash<long long>()(((long long)x.x)^(((long long)x.y)<<32));
    }
};
unordered_map <pii, int, HASH> mp;
*/

//map <pii, int> mp;
/*
//#include <ext/pb_ds/assoc_container.hpp>
//using namespace __gnu_pbds;
struct chash {
   int operator()(pii x) const { return x.x* 31 + x.y; }
};
gp_hash_table <pii, int, chash> mp;

bool comp (const pii& p1, const pii& p2) {
	return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}
*/

const int N = 1e5 + 10;
vector < vector <pili> > Adj;
int V;
long long memo[2*N + 1];

//vector <pii> edge;
/*
int bs(const pii& p) {
	int sz = (int)edge.size();
	int l = 0, h = sz - 1;
	while (l <= h) {
		int g = (l + h)>>1;
		if (p.x == edge[g].x && p.y == edge[g].y) return g;
		if (l == h && p != edge[g]) return -1;
		if (comp(p, edge[g])) h = g - 1;
		else l = g + 1;
	}
}
*/

long long dfs(int s, int pr, long long wt, int idx) {
	//int idx = mp[{pr, s}];
	//int idx = bs(pii(pr, s));

	if (memo[idx] != -1)
		return memo[idx];
	else {
		memo[idx] = wt;
		for (auto vPair : Adj[s]) {
			int v = vPair.x;
			long long w = vPair.y;
			int nxtIdx = vPair.idx;
			if (v == pr) continue;
			nax(memo[idx], dfs(v, s, w, nxtIdx) + wt);
		}
		return memo[idx];
	}
}

void solve() {
	vector <long long> Ans(V, 0);
	for (int u = 0; u < V; ++u) {
		for (auto vPair : Adj[u]) {
			int v = vPair.x;
			long long w = vPair.y;
			int nxtIdx = vPair.idx;
			nax(Ans[u], dfs(v, u, w, nxtIdx));
		}
	}

	for (auto it : Ans) printf("%lld ", (long long)it);
	printf("\n");
}

void read() {
	for (int i = 0; i < 2*N + 1; ++i) memo[i] = -1;
	int u, v, w;
	scanf (" %i", &V);
	Adj.clear();
	Adj.assign(V, vector <pili>());
	//edge.clear();
	//mp.clear();

	for (int e = 0; e < V - 1; ++e) {
		scanf (" %i %i %i", &u, &v, &w);
		--u, --v;
		Adj[u].push_back({v, w, 2*e});
		Adj[v].push_back({u, w, 2*e + 1});
		//mp[{u, v}] = 2*e;
		//mp[{v, u}] = 2*e + 1;
		//edge.push_back({u,v});
		//edge.push_back({v,u});
	}
	//sort (edge.begin(), edge.end(), comp);
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
