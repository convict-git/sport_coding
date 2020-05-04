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
const int N = 2010 + 100;
const int infi = (int)1e9;

struct Edge {
   int u, v, w;
   inline bool operator > (const Edge &o) const {
      return w > o.w;
   }
};
vector <Edge> edges;
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

void solve(int s, int t, int tc)  {
   cout << "Network " << tc << '\n' << "The bandwidth is ";
   cout << edmondsKarp(s, t) << ".\n\n";
}

void addPseudoVer (Edge e, int& pv) {
   Adj[e.u].push_back(pv);
   Adj[pv].push_back(e.u);
   Adj[e.v].push_back(pv);
   Adj[pv].push_back(e.v);

   f[e.u][pv] += e.w;
   f[pv][e.v] += e.w;

   Adj[e.v].push_back(pv + 1);
   Adj[pv + 1].push_back(e.v);
   Adj[e.u].push_back(pv + 1);
   Adj[pv + 1].push_back(e.u);

   f[e.v][pv + 1] += e.w;
   f[pv + 1][e.u] += e.w;

}

pii read() {
   int s, t, u, v, c, pv = n;
   cin >> s >> t >> m;
   --s, --t;
   n += 2 * m;
   Adj.assign(n, vector <int> ());
   edges.clear();

   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         f[i][j] = f[j][i] = 0;

   for (int i = 0; i < m; ++i) {
      cin >> u >> v >> c;
      --u, --v;
      edges.push_back({min(u,v), max(u,v), c});
   }

   for (Edge e : edges) {
      addPseudoVer(e, pv);
      pv += 2;
   }
   return pii(s, t);
}

signed main() {
   int tc = 0;
   while(cin >> n, n) {
      ++tc;
      pii tmp = read();
      solve(tmp.x, tmp.y, tc);
   }
   return EXIT_SUCCESS;
}

