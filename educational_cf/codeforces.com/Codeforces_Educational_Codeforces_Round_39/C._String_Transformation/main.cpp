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
   string s;
   cin >> s;
   int n = (int)s.size();

   int pos = 25;

   for (int i = n-1; pos >= 0 and i >= 0; --i) {
      if (s[i] - 'a' <= pos) {
         s[i] = char('a' + pos);
         --pos;
      }
   }

   if (pos == -1) {
      cout << s << '\n';
   }
   else cout << -1 << '\n';
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
