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

void solve() {
   int n;
   cin >> n;
   int tm = 1;
   for (int i = 0; i < n; ++i) {
      int l, r;
      cin >> l >> r;
      if (tm > r) {
         cout << 0 << ' ';
         continue;
      }
      else {
         tm = max(tm, l);
         cout << tm << ' ';
         ++tm;
      }
   }
   cout << '\n';
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
