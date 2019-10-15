#include         <iostream>
#include         <iomanip>
#include         <functional>
#include         <algorithm>
#include         <unordered_map>
#include         <vector>
#include         <map>
#include         <set>
#include         <chrono>
#include         <queue>
#include         <random>
#include         <string>
#include         <cstring>
#include         <climits>
#include         <cstdlib>
#include         <cmath>
#include         <iomanip>
#include         <cassert>
#define x        first
#define y        second
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;
using pii = pair <int, long long>;

const int N = int(2e6) + 10;

int V, E, vl, vis[N];
long long W[N], xl;
vector < vector <pii> > Adj;
pii g[N];

inline pii sol(int u, int v) {
    if (g[u].y == g[v].y)
        return (g[u].x < g[v].x ? g[u] : g[v]);
    else if (g[u].y > g[v].y)
        return g[u];
    else return g[v];

}

void dfs (int u, int pr, long long k) {
    vis[u] = 1;

    for (auto vPair : Adj[u]) {
        int v = vPair.x;
        if (v == pr) continue;
        if (!vis[v]) {
            dfs (v, u, k);
            g[u] = sol (u, v);
        }
    }
}

void read() {
    int tc;
    cin >> tc;
    while (tc--) {
        int n, q, u, v, w = 1;
        long long k;
        cin >> n >> q;
        xl = 0, vl = -1;
        V = n, E = n - 1;
        Adj.assign(V, vector <pii>());

        for (int i = 0; i < n; ++i)
            cin >> W[i];

        for (int e = 0; e < E; ++e) {
            cin >> u >> v;
            --u, --v;
            Adj[u].emplace_back(pii(v, w));
            Adj[v].emplace_back(pii(u, w)); // undirected
        }

        for (int i = 0; i < q; ++i) {
            cin >> u >> k;
            u ^= (vl + 1), k ^= xl;
            --u;
            for (int j = 0; j < n; ++j)
                vis[j] = 0, g[j] = pii (j, W[j] ^ k);

            dfs (0, -1, k);
            vl = g[u].x, xl = g[u].y;
            cout << vl + 1 << ' ' << xl << '\n';
        }
    }
}

signed main() {
    IOS; PREC;
    read();
	return EXIT_SUCCESS;
}

