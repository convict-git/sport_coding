#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    "[ " << #x << " : " << x << " ]"
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = 110;
const int infi = (int)1e9;

int f[N][N];
vector < vector <int> > Adj;
int n, m;
int Par[N];
int M, W;

int bfs (int s, int t) {
   fill (Par, Par + N, -1);
   Par[s] = -2;

   queue <pii> Q;
   Q.push(pii(s, infi));

   while (!Q.empty()) {
      pii tmp = Q.front();
      Q.pop();
      int u = tmp.x, flow = tmp.y;

      for (int v : Adj[u]) {
         if (Par[v] == -1 && f[u][v]) {
            Par[v] = u;
            int newFlow = min(flow, f[u][v]);
            if (v == t) {
               return newFlow;
            }
            Q.push(pii(v, newFlow));
         }
      }
   }
   return 0;
}

int edmondsKarp(int s, int t) {
   int flow = 0;
   int newFlow;

   while ((newFlow = bfs (s, t))) {
      flow += newFlow;
      int cur = t;
      while (cur != s) {
         int prv = Par[cur];
         f[prv][cur] -= newFlow;
         f[cur][prv] += newFlow;
         cur = prv;
      }
   }
   return flow;
}

inline void addEdge (int u, int v, int flow) {
   Adj[u].push_back(v);
   Adj[v].push_back(u);
   f[u][v] = flow;
}

void dfs (int u, bool inS[]) {
   inS[u] = true;
   for (int v : Adj[u]) {
      if (!inS[v] && f[u][v])
         dfs (v, inS);
   }
}

void solve() {
   int s = 2 * 0 + 1, t = 2 * (M - 1);
   Adj.assign(N, vector <int> ());
   for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
         f[i][j] = 0;

   for (int i = 0; i < M - 2; ++i) {
      int u, c;
      cin >> u >> c;
      --u;
      addEdge(2 * u, 2 * u + 1, c);
   }

   addEdge(s ^ 1, s, infi);
   addEdge(t, t ^ 1, infi);

   for (int i = 0; i < W; ++i) {
      int u, v, c;
      cin >> u >> v >> c;
      --u, --v;
      addEdge(2 * u + 1, 2 * v, c);
      addEdge(2 * v + 1, 2 * u, c);
   }
   int flow = edmondsKarp(s, t);
   cout << flow << '\n';
}

signed main() {
   while (cin >> M >> W, M || W) {
      solve();
   }
   return EXIT_SUCCESS;
}

