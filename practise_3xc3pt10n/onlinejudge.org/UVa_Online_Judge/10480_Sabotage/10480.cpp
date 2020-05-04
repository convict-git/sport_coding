#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second

#define bg(x)    "[ " << #x << " : " << x << " ]"
using namespace std;
using pii = pair <int,int>;

const int N = 55;
const int infi = (int)1e9;

int f[N][N];
vector < vector <int> > Adj;
int n, m;
int Par[N];

int bfs (int s, int t) {
   fill (Par, Par + n, -1);
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

void dfs (int u, bool inS[]) {
   inS[u] = true;
   for (int v : Adj[u]) {
      if (!inS[v] && f[u][v]) {
         dfs (v, inS);
      }
   }
}

inline void addEdge(int u, int v, int flow) {
   Adj[u].push_back(v);
   Adj[v].push_back(u);
   f[u][v] = flow;
   f[v][u] = flow;
}

void solve() {
   Adj.assign(N, vector <int> ());

   int s = 0, t = 1;
   for (int e = 0; e < m; ++e) {
      int u, v, c;
      cin >> u >> v >> c;
      --u, --v;
      addEdge(u, v, c);
   }

   int flow = edmondsKarp(s, t);
   //cerr << flow << '\n';
   bool inS[N] = {0};
   dfs (s, inS);

   vector <pii> cutEdges;
   for (int u = 0; u < n; ++u) {
      if (!inS[u]) continue;
      for (int v : Adj[u]) {
         if (inS[v]) continue;
         assert(f[u][v] == 0);
         cutEdges.push_back(pii(u + 1, v + 1));
      }
   }

   for (pii cut : cutEdges) {
      cout << cut.x << ' ' << cut.y << '\n';
   }
   cout << '\n';
}

signed main() {
   while (cin >> n >> m, n || m) {
      solve();
   }

   return EXIT_SUCCESS;
}

