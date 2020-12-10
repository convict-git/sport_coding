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
   int c1, c2, c3;
   cin >> c1 >> c2 >> c3;
   int mn = min({abs(c1 -c2), c2, c3});
   c1 -= mn, c2 -= mn, c3 -= mn;
   int sm = c1 + c2 + c3;
   if (sm % 3 == 0) {
      cout << "Santhosh\n";
   }
   else if (sm % 3 == 1) {
      cout << "Ahmed\n";
   }
   else {
      cout << "Rakesh\n";
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
