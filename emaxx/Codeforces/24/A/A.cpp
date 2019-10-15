#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;

const int N = 104;
const int infi = (int) 1e9;
vector < vector <int> > Adj;
vector <bool> used;
int W[N][N];
int n;
int cWsum, acWsum;

void dfs (int u, int pr, int f) {
    int A[N];
    for (int i = 0; i < n; ++i) {
        cin >> A[i];
    }

    if (f) used[u] = true;
    for (auto v : Adj[u]) {
        if (!used[v] && pr != v) {
            W[u][v] == infi ? cWsum += W[v][u] : acWsum += W[u][v];
            dfs (v, u, 1);
        }
    }
}

void read() {
    int a, b, c;
    cin >> n;
    Adj.resize(n);
    used.resize(n);
    cWsum = acWsum = 0;
    fill (used.begin(), used.end(), false);

    for (int i = 0; i < n; ++i) {
        cin >> a >> b >> c;
        --a, --b;
        W[a][b] = c;
        Adj[a].push_back(b);
        Adj[b].push_back(a);
    }

}

int main() {
    IOS; PREC;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            W[i][j] = infi;
    read();
    dfs(0, -1, 0);
    cout << min(cWsum, acWsum) << '\n';

    return EXIT_SUCCESS;
}
