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
   vector <double> p(n);
   for (int i = 0; i < n; ++i) {
      cin >> p[i];
   }

   // 3
   // 0.5 0.5 0.5
   // 13.750
   //
   // 000 - 9 * 0.5 * 0.5 * 0.5
   // x00 - 4
   // 0x0 - 2
   // 00x - 4
   // xx0 - 1
   // x0x - 1
   // 0xx - 1
   // xxx - 0
   //
   // 22 * 0.125
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
