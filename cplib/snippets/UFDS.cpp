#include <bits/stdc++.h>
using namespace std;
struct UFDS {
   static const int N = (int)1e6 + 10;
   UFDS (int n_) {
      n = n_;
      make_set();
   }
   int n;
   int rep[N], rnk[N], sz[N];

   void make_set() {
      for(int i = 0; i < n; ++i)
         rep[i] = i, rnk[i] = 0, sz[i] =  1;
   }

   int find_set(int u) {
      int ru = u;
      while (ru != rep[ru])
         ru = rep[ru];

      while (u != rep[u]) {
         int tmp = rep[u];
         rep[u] = ru;
         u = tmp;
      }
      return ru;
   }

   void merge_set(int u, int v) {
      int ru = find_set(u), rv = find_set(v);
      if (rnk[ru] > rnk[rv]) {
         rep[rv] = rep[ru];
         sz[ru] += sz[rv];
      }
      else {
         rep[ru] = rep[rv];
         sz[rv] += sz[ru];
      }

      if (rnk[ru] == rnk[rv]) {
         ++rnk[rv];
      }
   }
};
