#include <bits/stdc++.h>
using namespace std;
int head[N], num, V, E;
bool vis[N];
struct edge {
    int u, v;
    long long w;
    int nxt;
} e[M];


void addEdge(int u, int v, long long w = 1) {
    e[num].u = u;
    e[num].v = v;
    e[num].w = w;
    e[num].nxt = head[u];
    head[u] = num++;
}

void read() {
    int n, m, u, v;
    long long w = 1;
    num = 0;
    for (int i = 0; i < N; ++i)
        head[i] = -1, vis[i] = 0;

    cin >> n >> m;
    V = n, E = m;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        --u, --v;
        addEdge(u, v, w);
        addEdge(v, u, w);
    }
}
//for (int i = head[u]; i != -1; i = e[i].nxt)

