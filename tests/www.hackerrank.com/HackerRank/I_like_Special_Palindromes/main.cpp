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
   string s;
   cin >> s;
   int res = 0;
   for (int i = 0; i + 10 - 1 < n; ++i) {
      bool ok = true;
      for (int j = i; j < i + 10 - 1; ++j) {
         ok &= (s[j] == s[i + 10 - j - 1]);
      }
      res += ok;
   }
   cout << res << '\n';
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
