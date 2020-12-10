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


const int Mxn = 1e5+10;
int p[Mxn], rnk[Mxn];
inline int rep(int x) { return x == p[x] ? x : p[x] = rep(p[x]); }
inline void merge(int x, int y) {
   int rx = rep(x), ry = rep(y);
   if (rnk[rx] >= rnk[ry]) {
      p[ry] = rx;
      rnk[rx] += rnk[rx] == rnk[ry];
   }
   else p[rx] = ry;
}

void preproc() {
}

void solve() {
   string s;
   cin >> s;
   int res = 0;
   int n = (int)s.size();
   vector <int> forw;
   vector <int> bck;
   for (int i = 0; i < n; ++i) {

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
