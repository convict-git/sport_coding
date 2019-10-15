// lca library using segment trees
// This library is created by Priyanshu Shrivastav (mr.convict) // https://github.com/convict-git/sport_coding/blob/master/cplib/snippets/lca.cpp
#include <bits/stdc++.h>
using namespace std;

class LCA { // O(N) preprocessing, O(logN) queury
   vector <int> euler, height, f;
   vector <int> seg;
   int V, euler_sz;

   LCA (int n, vector <vector <int>> &T, int root = 0) {
      V = n;
      height.assign(n, 0);
      function <void(int, int, int)> dfs =
         [&] (int u, int pr, int h) -> void {
            height[u] = h;
            f[u] = (int)euler.size();
            euler.push_back(u);

            for (int v : T[u]) {
               if (v == pr) continue;
               dfs(v, u, h + 1);
               euler.push_back(u);
            }
         };
      dfs(root, -1, 0); // ROOT is considered 0 here by default

      euler_sz = (int)euler.size();
      seg.assign(euler_sz, 0);

      function <void(int, int, int)> create =
         [&] (int l, int r, int x) -> void {
            if (l == r) {
               seg[x] = euler[l];
               return;
            }
            int mid = (l + r)/2;
            create(l, mid, x + x + 1);
            create(mid + 1, r, x + x + 2);
            seg[x] = (height[seg[x + x + 1]] < height[seg[x + x + 2]]
                  ? seg[x + x + 1] : seg[x + x + 2]);
         };
   }

   int get_lca(int u, int v) { // expects 1..n indexing
      --u, --v;
      if (f[u] > f[v]) swap(u, v); // uh shit!

      function <int(int, int, int, int, int)> query = // returns the index
         [&] (int l, int r, int x, int ql, int qr) -> int {
            if (r < ql || l > qr) {
               return -1;
            }
            if (l >= ql && r <= qr) {
               return seg[x];
            }
            int mid = (l + r) / 2;
            int lu = query(l, mid, x + x + 1, ql, qr);
            int ru = query(mid + 1, r, x + x + 2, ql, qr);
            if (lu == -1) return ru;
            if (ru == -1) return lu;
            return (height[lu] < height[ru] ? lu : ru);
         };
      return query(0, euler_sz - 1, 0, f[u], f[v]);
   }
};
