#include <bits/stdc++.h>
using namespace std;
struct max_flow {
   int V;
   vector < vector <pii> > Adj;
   int Par[N];
   int cap[N][N], fcap[N][N];
   long long ds[N];

   max_flow(int V_) {
      V = V_;
      init();
   }

   void init () {
      assert(V);
      Adj.assign(V, vector <pii> ());
      for (int i = 0; i < V; ++i)
         for (int j = 0; j < V; ++j)
            fcap[i][j] = cap[i][j] = 0;
   }

   int spfa (int s, int t) {
      bool inQueue[N];
      int cnt[N];
      queue <int> q;
      for (int i = 0; i < V; ++i)
         ds[i] = inf, Par[i] = -1, inQueue[i] = false, cnt[i] = 0;

      ds[s] = 0, q.push(s), inQueue[s] = true;

      while (!q.empty()) {
         int u = q.front();
         q.pop();
         inQueue[u] = false;

         for (pii vPair : Adj[u])  {
            int v = vPair.x;
            long long cost = vPair.y;
            if (ds[v] > ds[u] + cost) {
               ds[v] = ds[u] + cost;
               Par[v] = u;
               if (!inQueue[v]) {
                  q.push(v);
                  inQueue[v] = true;
                  ++cnt[v];
                  assert (cnt[v] > V); // negative cost cycle
               }
            }
         }
      }

      if (ds[t] == inf) return 0;
      int flow = infi;
      int cur = t;
      while (cur != s) {
         int prv = Par[cur];
         flow = min(flow, fcap[prv][cur]);
         cur = prv;
      }
      return flow;
   }

   long long min_cost_K_flow (int s, int t, int K = infi) {
      for (int i = 0; i < V; ++i)
         for (int j = 0; j < V; ++j)
            fcap[i][j] = cap[i][j];

      int flow = 0;
      int newFlow;
      long long cost = 0;

      while ((newFlow = spfa(s, t)) && flow < K) {
         newFlow = min(newFlow, K - flow);
         flow += newFlow;
         cost += newFlow * ds[t];

         int cur = t;
         while (cur != s) {
            int prv = Par[cur];
            fcap[prv][cur] -= newFlow;
            fcap[cur][prv] += newFlow;
            cur = prv;
         }
      }

      // assert (flow != 0);
      if (flow < K) return -1; // CHECK ERROR //TODO
      else return cost;
   }

   inline void addEdge (int u, int v, long long cost, int flow) {
      Adj[u].push_back(pii(v, cost));
      Adj[v].push_back(pii(u, cost));
      cap[u][v] = flow;
   }
}

