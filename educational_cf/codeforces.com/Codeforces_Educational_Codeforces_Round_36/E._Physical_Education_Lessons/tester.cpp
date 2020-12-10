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
   int n, q;
   cin >> n >> q;
   vector <int> ar(n, 1);
   while (q--) {
      int l, r, k;
      cin >> l >> r >> k;
      --l, --r;
      for (int i = l; i <= r; ++i) {
         ar[i] = (k == 1 ? 0 : 1);
      }
      int cnt = 0;
      for (int i = 0; i < n; ++i)
         cnt += ar[i];
      cout << cnt << '\n';
   }
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
