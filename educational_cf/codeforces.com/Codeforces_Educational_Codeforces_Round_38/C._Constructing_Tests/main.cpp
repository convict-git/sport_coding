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
   int xi;
   cin >> xi;

   if (xi == 0) {
      cout << 1 << ' ' << 1 << '\n';
   }
   else if (xi == 1) {
      cout << -1 << '\n';
   }
   else {
      int n = 1, m;
      while (n * n - 1 < xi) {
         ++n;
      }
      cout << n << ' ' << (n/(n * n - xi)) << '\n';
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
