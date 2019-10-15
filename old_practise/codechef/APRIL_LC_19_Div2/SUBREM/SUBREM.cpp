#include         <iostream>
#include         <iomanip>
#include         <functional>
#include         <algorithm>
#include         <unordered_map>
#include         <vector>
#include         <map>
#include         <set>
#include         <queue>
#include         <string>
#include         <cstring>
#include         <climits>
#include         <cstdlib>
#include         <cmath>
#include         <iomanip>
#include         <cassert>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = (int)1e6 + 10;
const int infi = (int)1e9;
int X, A[N], vis[N];
long long f[N];

int V, E;
vector < vector <pii> > Adj;

void dfs (int u, int pr) {
    vis[u] = 1;

    f[u] = A[u];
    for (auto vPair : Adj[u]) {
        int v = vPair.x;
        if (v == pr) continue;
        if (!vis[v]) dfs (v, u);
        f[u] += max(f[v], -1ll*X);
    }
}

void solve() {
    dfs (0, -1);
    cout << max(f[0], -1ll*X) << '\n';
}

void read() {
	int n, u, v, w = 1;

    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> X;
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
            f[i] = -infi, vis[i] = 0;
        }

        V = n, E = n - 1;
        Adj.assign(V, vector <pii>());

        for (int e = 0; e < E; ++e) {
            cin >> u >> v;
            Adj[u - 1].emplace_back(pii(v - 1, w));
            Adj[v - 1].emplace_back(pii(u - 1, w)); // undirected
        }
        solve();
    }
}

signed main() {
    IOS; PREC;
    read();

	return EXIT_SUCCESS;
}
