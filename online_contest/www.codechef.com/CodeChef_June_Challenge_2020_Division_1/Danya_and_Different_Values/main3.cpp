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

const int mxn=2e5+10;
const int inf=INT_MAX;
int n, q;
int p[mxn], ar[mxn], vis[mxn], d[mxn], pre[mxn], post[mxn], nxt[2 * mxn], mp[mxn];
vector <int> euler;
vector <int> g[mxn];

struct Node {
   int sz, *v;
   void initNode (int idx) {
      sz = 1;
      v = new int [1];
      v[0] = nxt[idx];
      return;
   }
   void mergeNode (const Node &L, const Node &R) {
      sz = L.sz + R.sz;
      v = new int [sz];
      for (int i = 0; i < L.sz; ++i) v[i] = L.v[i];
      for (int i = 0; i < R.sz; ++i) v[i+L.sz] = R.v[i];
      sort(v, v+sz);
   }
   int getDiffVal (const int &rLim) {
      int L=0, H=sz-1;
      while (L <= H) {
         int G=(L+H)/2;
         if (v[G] <= rLim) L=G+1;
         else H=G-1;
      }
      return sz-(H+1);
   }
};

Node sg[8 * mxn];
void createTree (int l, int r, int x) {
   if (l == r) {
      sg[x].initNode(l);
      return;
   }
   int mid = (l+r)/2;
   createTree(l, mid, x+x+1);
   createTree(mid+1, r, x+x+2);
   sg[x].mergeNode(sg[x+x+1], sg[x+x+2]);
}

int get (int ql, int qr, int l, int r, int x, const int &rLim) {
   if (l > qr || r < ql) return 0;
   if (l >= ql && r <= qr)
      return sg[x].getDiffVal(rLim);
   int mid = (l+r)/2;
   return
      get(ql, qr, l, mid, x+x+1, rLim)
      + get(ql, qr, mid+1, r, x+x+2, rLim);
}

void reset() {
   euler.clear();
   for (int i = 0; i <= n; ++i) {
      g[i].clear();
      ar[i] = pre[i] = post[i] = vis[i] = d[i] = p[i] = 0;
      nxt[i*2] = nxt[i*2 + 1] = inf;
      mp[i] = inf;
   }
}

void preproc() {
}

void solve() {
   bool sbtask2=true;
   cin >> n;
   reset();
   // take input
   for (int e = 0, u, v; e < n-1; ++e) {
      cin >> u;
      --u;
      v = e+1; // 1....n-1
      g[u].push_back(v);
      p[v] = u;
      if (p[v] != v - 1) {
         sbtask2 = false;
      }
   }
   for (int i = 0; i < n; ++i) {
      cin >> ar[i];
   }
   cin >> q;
   function <void(int, int)> dfs = [&] (int u, int dep) {
      d[u] = dep;
      pre[u] = (int)euler.size();
      euler.push_back(u);
      for (int v : g[u]) {
         dfs(v, dep+1);
      }
      post[u] = (int)euler.size();
      euler.push_back(u);
   };
   dfs(0, 0);
   for (int i = 2*n-1; i >= 0; --i) {
      int u = euler[i];
      nxt[i] = mp[ar[u]];
      mp[ar[u]] = i;
   }
   createTree(0, 2*n-1, 0);

   int u, D;
   int res = 0;
   while (q--) {
      cin >> u >> D;
      u ^= res, D ^= res;
      --u;
      if (sbtask2) { // path tree
         res = get(0, 2*n-1, pre[u], pre[u]+D, 0, pre[u]+D);
         cout << res << '\n';
      }
      else { // brute force
         set <int> s;
         for (int i = pre[u]; i <= post[u]; ++i) {
            int v = euler[i];
            if (d[v] <= d[u] + D) {
               s.insert(ar[v]);
            }
         }
         res = (int)s.size();
         cout << res << '\n';
      }
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
