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

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;
using pii = pair <int, int>;

const int N = int(1e6) + 10;

int V, E, vis[N], treeDeg[N];
vector < vector <pii> > Adj;
set <int> leaves;
long long f[N], m[N], g[N];

inline long long gcd (long long a, long long b) {
    return (b == 0 ? a : gcd (b, a % b));
}

void dfs (int u, int pr) {
    vis[u] = 1;
    if (pr != -1)
        g[u] = gcd (f[u], g[pr]);
    else g[u] = f[u];

    for (auto vPair : Adj[u]) {
        int v = vPair.x;
        if (v == pr) continue;
        if (vis[v] == 0) {
            ++treeDeg[u];
            dfs (v, u);
        }
    }

    if (treeDeg[u] != 0) return;
    else {
        leaves.insert(u);
        g[u] = gcd (g[u], m[u]);
    }
}

void solve() {
    dfs (0, -1);

    for (int l : leaves)
        cout << g[l] * (long long)((m[l] - 1)/g[l]) << ' ';
    cout << '\n';
}

void read() {
	int n, u, v, w = 1;
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        V = n, E = n - 1;
        Adj.assign(V, vector <pii>());
        leaves.clear();

        for (int i = 0; i < n; ++i)
            vis[i] = 0, g[i] = -1, treeDeg[i] = 0;

        for (int e = 0; e < E; ++e) {
            cin >> u >> v;
            Adj[u - 1].emplace_back(pii(v - 1, w));
            Adj[v - 1].emplace_back(pii(u - 1, w)); // undirected
        }

        for (int i = 0; i < n; ++i)
            cin >> f[i];
        for (int i = 0; i < n; ++i)
            cin >> m[i];

        solve();
    }
}

signed main() {
    IOS; PREC;
    read();
	return EXIT_SUCCESS;
}








