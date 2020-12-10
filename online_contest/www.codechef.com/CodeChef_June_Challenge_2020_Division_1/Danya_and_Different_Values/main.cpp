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

const int inf=1e9;
const int mxn=2e5;
int pre[mxn], post[mxn], dep[mxn], ar[mxn];
vector <int> euler;

struct outNode {
   pair <int, int> *v;
   int sz;
   ///
   struct inNode {
      int *v2, sz2;
      void initInNode (int x) { v2 = new int[1]; v2[0] = x, sz2 = 1; }
      void mergeInNode (const inNode &l, const inNode &r) {
         sz2 = l.sz2 + r.sz2;
         v2 = new int  [sz2];
         for (int i = 0; i < l.sz2; ++i) v2[i] = l.v2[i];
         for (int i = 0; i < r.sz2; ++i) v2[l.sz2+i] = r.v2[i];
         // sort(v2, v2 + sz2);
      }
      int getRes (const int &rLimit) {
         int L = 0, H = sz2-1;
         while (L <= H) { int g = (L+H) / 2;
            if (v2[g] < rLimit) L=g+1;
            else H=g-1;
         }
         return sz2 - (H+1);
      }
   };
   inNode *Ti;
   void createInTree(int l, int r, int x) {
      if (l == r) {
         Ti[x].initInNode(v[l].second);
         return;
      }
      int mid = (l+r)/2;
      createInTree(l, mid, x+x+1);
      createInTree(mid+1, r, x+x+2);
      Ti[x].mergeInNode(Ti[x + x + 1], Ti[x + x + 2]);
   }
   int getFromInTree (int ql, int qr, int l, int r, int x, const int &rLim) {
      if (l > qr || r < ql) return 0;
      if (l >= ql && r <= qr) {
         return Ti[x].getRes(rLim);
      }
      int mid=(l+r)/2;
      return getFromInTree(ql, qr, l, mid, x+x+1, rLim)
         + getFromInTree(ql, qr, mid+1, r, x+x+2, rLim);
   }
   ///

   void initOutNode (const int &idx) { // index of euler tour
      sz = 1;
      v = new pair <int, int> [1];
      int u = euler[idx];
      v[0] = make_pair(dep[u], ar[u]);

      Ti = new inNode[4 * sz]; // create inner tree
      createInTree(0, sz-1, 0);
   }
   void mergeOutNode(const outNode &l, const outNode &r) {
      sz = l.sz + r.sz;
      v = new pair <int, int> [sz];
      for (int i = 0; i < l.sz; ++i) v[i] = l.v[i];
      for (int i = 0; i < r.sz; ++i) v[l.sz+i] = r.v[i];
      sort(v, v + sz);

      Ti = new inNode[4 * sz]; // create inner tree
      createInTree(0, sz-1, 0);
   }
   int getMeRes (const int &dLim, const int &rLim) { // less than equal to Dlimit
      int L = 0, H = sz-1;
      while (L <= H) { int g = (L+H) / 2;
         if (v[g].first <= dLim) L=g+1;
         else H=g-1;
      }
      return getFromInTree(0, sz-1, 0, H, 0, rLim);
   }
};

outNode To[4*mxn+1];
// create the next array

void createOutTree (int l, int r, int x) {
   if (l == r) {
      To[x].initOutNode(l);
      return;
   }
   int mid=(l+r)/2;
   createOutTree(l, mid, x+x+1);
   createOutTree(mid+1, r, x+x+2);
   To[x].mergeOutNode(To[x+x+1], To[x+x+2]);
}

int get (int ql, int qr, int l, int r, int x, const int &D, const int &R) {
   if (l > qr || r < ql) return 0;
   if (l >= ql && r <= qr) {
      return To[x].getMeRes(D, R);
   }
   int mid=(l+r)/2;
   return get(ql, qr, l, mid, x+x+1, D, R)
      + get(ql, qr, mid+1, r, x+x+2, D, R);
}

int work(int L, int R, int u, int D, int n) {
   debug(L, R, u, D, n);
   return get(L, R, 0, 2 * n - 1, 0, D, R);
}

void preproc() {
}

void solve() {
   // take input
   int n;
   cin >> n;
   vector <int> pi(n);
   vector <vector <int>> T;
   T.assign(n, vector <int> ());
   for (int i = 1; i <= n-1; ++i) {
      cin >> pi[i];
      int u = i, v = pi[i] - 1;
      T[u].push_back(v);
      T[v].push_back(u);
   }
   for (int i = 0; i < n; ++i) {
      cin >> ar[i];
   }

   // creater euler array
   vector <bool> vis(n);
   function <void(int, int)> dfs = [&] (int u, int d) -> void {
      vis[u] = true;
      dep[u] = d;
      pre[u] = (int)euler.size();
      euler.push_back(u);
      for (int v : T[u]) {
         if (!vis[v]) {
            dfs(v, d + 1);
         }
      }
      post[u] = (int)euler.size();
      euler.push_back(u);
   };
   dfs(0, 0);

   // do something here !!!
   // some datastructure ? Maybe treaps if they say so?
   createOutTree(0, 2 * n - 1, 0);

   // process queries
   int q, res = 0;
   cin >> q;
   for (int i = 0; i < q; ++i) {
      int u, d;
      cin >> u >> d;
      u ^= res, d ^= res;
      int L = pre[u-1], R = post[u-1];
      res = work(L, R, u-1, d + dep[u], n);
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
