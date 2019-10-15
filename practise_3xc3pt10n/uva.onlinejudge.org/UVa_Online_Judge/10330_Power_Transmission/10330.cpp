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
using pii = pair <int,int>;

const int N = 100 * 2 + 2;
const int infi = (int)1e9;

int f[N][N];
vector < vector <int> > Adj;
int Par[N];
int n, m, nm, B, D;

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

long long edmondsKarp(int s, int t) {
   long long flow = 0;
   int newFlow;

   while ((newFlow = bfs (s, t))) {
      flow += 1ll * newFlow;
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

void addEdge (int u, int v, int flow) {
   Adj[u].push_back(v);
   Adj[v].push_back(u);
   f[u][v] = flow;
}

void solve() {
   Adj.assign(N, vector <int> ());
   for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
         f[i][j] = 0;

   int s = N - 2, t = N - 1;

   int u, v, c;
   for (int i = 0; i < nm; ++i) {
      cin >> c;
      addEdge(2 * i, 2 * i + 1, c);
   }
   cin >> m;
   for (int e = 0; e < m; ++e) {
      cin >> u >> v >> c;
      --u, --v;
      addEdge(2 * u + 1, 2 * v, c);
   }

   cin >> B >> D;
   for (int i = 0; i < B + D; ++i) {
      cin >> v;
      --v;
      if (i < B) addEdge(s, 2 * v, infi);
      else addEdge(2 * v + 1, t, infi);
   }
   cout << edmondsKarp (s, t) << '\n';
}

signed main() {
   while (cin >> nm) {
      solve();
   }

   return EXIT_SUCCESS;
}

