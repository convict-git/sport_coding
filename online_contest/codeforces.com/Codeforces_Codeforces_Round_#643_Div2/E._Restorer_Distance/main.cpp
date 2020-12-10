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
   int n, a, r, m;
   cin >> n >> a >> r >> m;
   vector <int> h(n);
   vector <long long> pref(n);
   for (int i = 0; i < n; ++i) {
      cin >> h[i];
   }

   sort(h.begin(), h.end());
   for (int i = 0; i < n; ++i) {
      pref[i] = (i ? pref[i - 1] : 0ll) + h[i];
   }

   long long res = LLONG_MAX;
   for (int i = 0; i < n; ++i) {
      long long cur = 0;
      long long mvup = 1ll * h[i] * i - (i ? pref[i - 1] : 0);
      long long mvdw = pref[n - 1] - pref[i] - 1ll * h[i] * (n - i - 1);

      if (mvup < mvdw) { // remove some bricks
         long long rem = mvdw - mvup;
         if (rem % n == 0) {
            cur += min(rem * r, rem * m);
         }
         else cur += rem * r;
         cur += (mvdw - rem) * min(m, r + a);
      }
      else { // add some bricks
         long long add = mvup - mvdw;
         if (add % n == 0) {
            cur += min(add * a, add * m);
         }
         else cur += add * a;
         cur += (mvup - add) * min(m, r + a);
      }
      res = min(cur, res);
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
