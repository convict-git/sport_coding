#include <bits/stdc++.h>
using namespace std;
long long cost[N];
class Compare {
   public:
      bool operator () (const int &u, const int &v) {
         return cost[u] > cost[v];
      }
};

bool prims () {
   bool vis[N] = {0};
   long long totalCost = 0;
   int edgeCnt = 0;

   for (int i = 0; i < n; ++i)
      cost[i] = inf, vis[i] = false;

   //priority_queue <pii, vector <pii>, greater <pii> > Q;
   set <int, Compare> Q;

   cost[0] = 0;
   //Q.push(pii(cost[0], 0));
   Q.insert(0);

   while (!Q.empty()) {
      //pii tmp = Q.top();
      //Q.pop();
      //int u = tmp.y;
      int u = *Q.begin();
      Q.erase(Q.begin());

      if (vis[u]) continue;
      if (cost[u] == inf) return false;
      vis[u] = true;
      totalCost += cost[u];

      for (auto vPair : AdjPQ[u]) {
         int v = vPair.x;
         long long w = vPair.y;
         if (!vis[v] && cost[v] > w) {
            cost[v] = w;
            //Q.push(pii(cost[v], v));
            Q.insert(v);
         }
      }
   }
   return true;
}


