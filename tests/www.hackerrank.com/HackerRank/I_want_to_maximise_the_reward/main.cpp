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
   int n, k;
   cin >> n >> k;
   string s;
   cin >> s;
   vector <int> dp(26);
   int res = 0;
   for (int i = 0; i < n; ++i) {
      int al = s[i] - 'a';
      int lst_max = 0;
      for (int c = 0; c < al; ++c) {
         lst_max = max(lst_max, dp[c]);
      }
      dp[al] = max(dp[al], lst_max + 1);
      res = max(res, dp[al]);
   }
   cout << 1ll * (res - 1) * k << '\n';
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
