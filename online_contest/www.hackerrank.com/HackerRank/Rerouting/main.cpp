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
const int Mxn = 3e5 + 10;
int N;
int outDeg[Mxn], vis[Mxn], rep[Mxn], rnk[Mxn];

void preproc() {
}

inline int get (int x) { return x == rep[x] ? x : rep[x] = get(rep[x]); }
inline void merge (int x, int y) {
   int rx = get(x), ry = get(y);
   if (rnk[rx] >= rnk[ry]) {
      rep[ry] = rx;
      if (rnk[rx] == rnk[ry]) {
         ++rnk[rx];
      }
   }
   else rep[rx] = ry;
}

void solve() {
   cin >> N;
   iota(rep, rep+N, 0);
   bool noLeaf = true;
   for (int i = 0; i < N; ++i) {
      int ai; cin >> ai; --ai;
      if (i != ai) {
         merge(i, ai);
         outDeg[i] += 1;
      }
   }
   int res = 0;
   for (int i = 0; i < N; ++i)  {
      if (outDeg[i] == 0) {
         ++res;
         vis[get(i)] = true;
         noLeaf = false;
      }
   }
   for (int i = 0; i < N; ++i) {
      int rp = get(i);
      if (!vis[rp]) {
         ++res;
         vis[rp] = true;
      }
   }
   if (noLeaf) {
      res += 1;
   }
   cout << res - 1 << '\n';
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
