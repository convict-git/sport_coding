#include <bits/stdc++.h>
using namespace std;
using pii = pair <int, int>
vector < vector <int> > Adj;
vector <pii> cutEdges;
bool inS[N];
int Par[N];
int cap[N][N], f[N][N];
int n, m;
const int infi = 1e9;

void init () {
   assert(n);
   Adj.assign(n, vector <int> ());
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         f[i][j] = cap[i][j] = 0;
   cutEdges.clear();
   fill (inS, inS + n, false);
}

int bfs (const int &s, const int &t) {
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

int edmondsKarpMaxFlow(const int &s, const int &t, const int &K = infi) {
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         f[i][j] = cap[i][j];

   int flow = 0;
   int newFlow;

   while ((newFlow = bfs (s, t)) && flow < K) {
      newFlow = min(newFlow, K - flow);
      flow += newFlow;
      int cur = t;
      while (cur != s) {
         int prv = Par[cur];
         f[prv][cur] -= newFlow;
         f[cur][prv] += newFlow;
         cur = prv;
      }
   }

   assert (flow < K);
   // assert (flow != 0);
   return flow;
}

void dfs(int u) {
   inS[u] = true;
   for (int v : Adj[u])
      if (!inS[v]) dfs(v);
}

void findCutEdges() {
   cutEdges.clear();
   for (int u = 0; u < n; ++u) {
      if (!inS[u]) continue;
      for (int v : Adj[u]) {
         if (inS[v]) continue;
         if (f[u][v] == 0) cutEdges.push_back(pii(u, v));
      }
   }
}

inline void addEdge (int u, int v, int flow) {
   Adj[u].push_back(v);
   Adj[v].push_back(u);
   cap[u][v] = flow;
}
