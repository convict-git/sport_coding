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
   string s="codeforces";
   long long k;
   cin >> k;
   long long pow=1;
   vector <int> cnt(10, 1);
   for (int i = 0; pow < k; i = (i+1) % 10) {
      pow /= cnt[i];
      ++cnt[i];
      pow *= cnt[i];
   }
   for (int i = 0; i < 10; ++i) {
      while (cnt[i]--) cout << s[i];
   }
   cout << '\n';
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
