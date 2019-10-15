#include <bits/stdc++.h>
using namespace std;
struct twoSAT {
   static const int N = (int)2e5 + 10;
   int n; // total number of variables * 2
   vector < vector < int> > G, GT;
   vector <int> order;
   int comp[N];
   bool used[N], assignment[N];
   twoSAT (int _n) : n(_n) {
      init();
   }
   void add_edge(int u, int v) {
      G[u].push_back(v);
      GT[v].push_back(u);
   }
   void init() {
      assert (n && n % 2 == 0); // n non-zero and even(x , ~x)
      G.assign(n, vector <int> ());
      GT.assign(n, vector <int> ());
      order.clear();
      for (int i = 0; i < n; ++i) {
         used[i] = assignment[i/2] = false;
         comp[i] = -1;
      }
   }

   void dfs_order(const int &u) {
      used[u] = true;
      for (int v : G[u]) if (!used[v]) dfs_order(v);
      order.push_back(u);
   }

   void dfs_cc(int u, int idx) {
      comp[u] = idx;
      for (int v : GT[u]) // in the reverse graph
         if (comp[v] == -1) dfs_cc(v, idx);
   }

   pair <bool, vector <int>> solve() {
      vector <int> sol;
      int cc = 0;
      for (int u = 0; u < n; ++u)
         if (!used[u]) dfs_order(u);

      assert(order.size());
      reverse(order.begin(), order.end());
      for(const int &u : order)
         if (comp[u] == -1) dfs_cc(u, cc++);

      for (int i = 0; i < n/2; ++i) {
         if (comp[2 * i] == comp[2 * i + 1])
            return make_pair(false, vector <int>()); // same component contradiction

         assignment[i] = comp[2 * i] > comp[2 * i + 1]; // x -> ~x then x is false
         sol.push_back(assignment[i]);
      }
      return make_pair(true, sol);
   }
};
