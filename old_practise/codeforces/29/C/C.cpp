//#pragma GCC      optimize ("Ofast")
#include         <map>
#include         <set>
#include         <cmath>
#include         <vector>
#include         <string>
#include         <cstring>
#include         <climits>
#include         <cstdlib>
#include         <iomanip>
#include         <cassert>
#include         <iomanip>
#include         <iostream>
#include         <algorithm>
#include         <functional>
#define pb       push_back
#define eb       emplace_back
#define se       second
#define fi       first
#define all(v)   (v).begin(),(v).end()
#define bug(s,x) fprintf(stderr,"[%s %s : %i]\n",s,#x,x),fflush(stderr)
#define bg(x)    bug ("bug : ", x)
#define inf      (0x7fffffff)
#define eps      ((double)1e-9)
#define scanf    warnscanf_shit = scanf
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed

using namespace std;
int warnscanf_shit;
typedef long long ll;
typedef unsigned long long ull;
const int MOD = 1e9 + 7;
const int MAXN = 1e5 + 10;

int n, startPoint = -1, endPoint = -1, sz;
vector < vector <int> > edge;
vector <pair <int, int> > vi;
set <int> s;
map <int, int> mp1, mp2;
vector <int> vis, pathStore;

void dfs (int u) {
	vis[u] = 1;
	pathStore.push_back (u);
	for (auto v : edge[u]) {
		if (vis[v] == 0)
			dfs (v);
	}
}

void solve() {
	for (int i = 0; i < (int) vi.size(); ++i) {
		int u, v;
		u = mp1[vi[i].first];
		v = mp1[vi[i].second];
		edge[u].push_back (v);
		edge[v].push_back (u);
	}
	for (int i = 0; i < (int) edge.size(); ++i) {
		if (edge[i].size() == 1) {
			startPoint == -1 ? startPoint = i : endPoint = i;
		}
	}
	vis.resize(sz);
	for (auto &ver : vis) ver = 0;
	dfs (endPoint);
	assert ((int)pathStore.size() == sz);
	for (int i = 0; i < sz; ++i) {
		int u = mp2[pathStore[i]];
		cout << u << ' ';
	}
	cout << '\n';
}

int main() {
	IOS; PREC;
	int u, v;
	cin >> n;
	while (n--) {
		cin >> u >> v;
		vi.push_back ({u, v});
		s.insert (u), s.insert (v);
	}
	sz = (int) s.size();
	edge.resize(sz);
	int it = 0;
	for (auto ver : s) {
		mp1[ver] = it;
		mp2[it] = ver;
		++it;
	}
	solve();

	return EXIT_SUCCESS;
}

