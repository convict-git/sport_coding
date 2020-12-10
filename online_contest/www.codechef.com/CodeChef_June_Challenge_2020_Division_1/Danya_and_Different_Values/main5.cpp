#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

void preproc() {
}

struct Node {
   vector <int> v;
   void initNode (int val) {
      v.push_back(val);
   }
   void mergeNode (const Node &L, const Node &R) {
      for (int el : L.v) v.push_back(el);
      for (int el : R.v) v.push_back(el);
      sort(v.begin(), v.end());
   }
   int get (int rLim) {
      int L=0, H=(int)v.size()-1;
      while (L <= H) {
         int g=(L+H)/2;
         if (v[g] <= rLim) L=g+1;
         else H=g-1;
      }
      return (int)v.size()-(H+1);
   }
};
void solve() {
   bool lineGraph=true;
   int n;
   cin >> n;
   vector <vector <int>> G;
   G.assign(n, vector <int> ());
   vector <int> ar(n);
   for (int v = 1; v <= n-1; ++v) {
      int u; cin >> u; --u;
      G[u].push_back(v);
      lineGraph &= (u == v-1);
   }
   for (int i = 0; i < n; ++i) {
      cin >> ar[i];
   }
   vector <Node> sg(4 * n);
   vector <int> nxt(n);
   vector <int> mp(n+1, INT_MAX);
   function <void(int, int, int)> create = [&] (int l, int r, int x) {
      if (l == r) {
         sg[x].initNode(nxt[l]);
         return;
      }
      int mid=(l+r)/2;
      create(l, mid, x+x+1);
      create(mid+1, r, x+x+2);
      sg[x].mergeNode(sg[x+x+1], sg[x+x+2]);
   };
   function <int(int, int, int, int, int, int)> get = [&]
      (int ql, int qr, int l, int r, int x, int rLim) -> int {
         if (l > qr || r < ql) return 0;
         if (l >= ql && r <= qr) {
            return sg[x].get(rLim);
         }
         int mid=(l+r)/2;
         return
            get(ql, qr, l, mid, x+x+1, rLim)
            + get(ql, qr, mid+1, r, x+x+2, rLim);
      };
   for (int u = n-1; u >= 0; --u) {
      nxt[u] = mp[ar[u]];
      mp[ar[u]] = u;
   }
   create(0, n-1, 0);
   set <int> s;
   function <void(int, int, int)> dfs = [&] (int u, int d, int D) {
      if (d > D) return;
      s.insert(ar[u]);
      for (int v : G[u]) {
         dfs(v, d+1, D);
      }
   };
   int q, res=0;
   cin >> q;
   while (q--) {
      int u, D;
      cin >> u >> D;
      u ^= res, D ^= res;
      --u;
      if (lineGraph) { // sbtask2
         int R = min(n-1, u+D);
         res = get(u, R, 0, n-1, 0, R);
      }
      else { // bruteforce
         s.clear();
         dfs(u, 0, D);
         res = (int)s.size();
      }
      cout << res << '\n';
   }
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
