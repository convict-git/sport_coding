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

int n;
vector <vector <int>> T;
vector <pair <int, int>> order;
vector <int> rep;
vector <int> sz;

inline int Rep (int x) {
   return x == rep[x] ? x : rep[x] = Rep(rep[x]);
}

long long calc () {
   rep.assign(n, 0);
   iota(rep.begin(), rep.end(), 0);
   sz.assign(n, 1);
   long long res = 0;
   vector <int> vis(n);
   for (auto pp : order) {
      int u = pp.second, val = pp.first, ru = Rep(u);
      vis[u] = true;
      long long thru = 0, cross = 0, pref = 0;
      for (int v : T[u]) {
         if (vis[v]) { // valid child,
            int rv = Rep(v);
            int s = sz[rv];
            thru += s;
            cross += pref * s;
            pref += s;
            rep[rv] = ru;
            sz[ru] += sz[rv];
         }
      }
      ++thru;
      res += (thru + cross) * val;
   }
   return res;
}

void solve() {
   cin >> n;
   vector <int> ar(n);
   T.assign(n, vector <int> ());
   for (int i = 0; i < n; ++i) {
      cin >> ar[i];
      order.push_back(make_pair(ar[i], i));
   }
   for (int e = 0, u, v; e < n-1; ++e) {
      cin >> u >> v;
      --u, --v;
      T[u].push_back(v);
      T[v].push_back(u);
   }

   // difference between max and min value on a simple path x,y = I(x,y)
   // Mx(x, y) and Mn(x, y)
   // cal for mx
   sort(order.begin(), order.end());
   long long mx = calc();
   // cal for mn
   sort(order.begin(), order.end(), greater <pair <int ,int>> ());
   long long mn = calc();
   cout << mx - mn << '\n';
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  // cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
