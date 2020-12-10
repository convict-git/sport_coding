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
   // a1, a2, .... al, ... , ar, ...an-1, an
   // inv_new = inv_old - inv(l, r) + C(r-l+1, 2) - inv(l, r)
   // inv_new Mod 2 = (inv_old - 2 * inv(l, r) + C(r-l+1, 2)) Mod 2
   // inv_new Mod 2 = (inv_old + C(r-l+1, 2)) Mod 2
   int n;
   cin >> n;
   vector <int> ar(n);
   for (int i = 0; i < n; ++i) {
      cin >> ar[i];
   }
   int inv = 0;
   for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
         inv += ar[j] < ar[i];
      }
   }
   int q;
   cin >> q;
   while (q--) {
      int l, r;
      cin >> l >> r;
      int len = r - l + 1;
      inv = (int) (((1ll * len * (len - 1)) / 2 + inv) % 2);
      cout << (inv ? "odd\n" : "even\n");
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

