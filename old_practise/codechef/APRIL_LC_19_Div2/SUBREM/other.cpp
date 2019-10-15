#include         <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = int(1e6) + 10;
const int M = int(1e6) + 10;
const int MAX = int(1e9);

int head[N], num, V, E;
bool vis[N];
struct edge {
    int u, v;
    long long w;
    int nxt;
} e[M];
int A[N];
ll dp[N], cost;

void dfs (int u, int pr) {
    vis[u] = 1;

    dp[u] = 1ll*A[u];
    for (int i = head[u]; i != -1; i = e[i].nxt) {
        int v = e[i].v;
        if (v == pr) continue;
        if (!vis[v])
            dfs(v, u);
        dp[u] = dp[u] + max(dp[v], cost);
    }
}

void addEdge(int u, int v, long long w = 1) {
    e[num].u = u;
    e[num].v = v;
    e[num].w = w;
    e[num].nxt = head[u];
    head[u] = num++;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie (nullptr);
    cout.precision (10); cout << fixed;
    int n, u, v;
    int tc;
    cin >> tc;
    while (tc--) {
        num = 0;
        cin >> n >> cost;
        cost *= -1;
        for (int i = 0; i < n; ++i) {
            cin >> A[i];
            head[i] = -1, vis[i] = 0;
        }

        for (int i = 0; i < n - 1; ++i) {
            cin >> u >> v;
            --u, --v;
            addEdge(u, v, 1);
            addEdge(v, u, 1);
        }

        dfs (0, -1);
        cout << max (dp[0], cost) << '\n';
    }
    return 0;
}


