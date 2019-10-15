#include         <bits/stdc++.h>
#define ll       long long
using namespace std;

const int N = (int)1e6 + 10;
const int M = (int)1e6 + 10;

int head[N], num, dg[N];
set <int> lv;
ll gc[N], mi[N];
bool vis[N];
struct edge {
    int u, v;
    long long w;
    int nxt;
} e[M];

ll cal (ll x, ll y) {
    if (y == 0) return x;
    else return cal (y, x % y);
}

void addEdge(int u, int v, ll w) {
    e[num].u = u;
    e[num].v = v;
    e[num].w = w;
    e[num].nxt = head[u];
    head[u] = num++;
}

void dfs (int u, int pr) {
    vis[u] = 1;
    if (pr != -1) gc[u] = cal (gc[u], gc[pr]);

    for (int i = head[u]; i != -1; i = e[i].nxt) {
        int v = e[i].v;
        if (pr == v) continue;
        if (!vis[v]) {
            ++dg[u];
            dfs (v, u);
        }
    }
    if (dg[u] == 0) {
        lv.insert(u);
        gc[u] = cal (gc[u], mi[u]);
    }
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie (nullptr);
    cout.precision (10); cout << fixed;
    int t;
    cin >> t;
    while (t--) {
        int n, u, v;
        num = 0;
        lv.clear();

        cin >> n;
        for (int i = 0; i < n; ++i)
            head[i] = -1, vis[i] = 0, dg[i] = 0;

        for (int i = 0; i < n - 1; ++i) {
            cin >> u >> v;
            --u, --v;
            addEdge(u, v, 1);
            addEdge(v, u, 1);
        }

        for (int i = 0; i < n; ++i) cin >> gc[i];
        for (int i = 0; i < n; ++i) cin >> mi[i];

        dfs (0, -1);
        for (auto it = lv.begin(); it != lv.end(); ++it) {
            int uit = *it;
            cout << gc[uit] * (ll)((mi[uit] - 1)/gc[uit]) << ' ';
        }
        cout << '\n';
    }
	return 0;
}

