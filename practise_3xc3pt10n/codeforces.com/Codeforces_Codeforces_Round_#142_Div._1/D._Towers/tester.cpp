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
   // a1 a2 .... an
   // n * n  + h something?
   // dp[i][j] worked on prefixes 1...i and last stack was made from [j...i]
   // dp[i][j] = if (sm[k, j - 1] <= sm[j, i]) dp[j - 1][k] + (j - i + 1 - 1);
   // so now we have fixed h[j...i]
   // no .of state :  n * n, time taken for each state : n - > O(n^3), won't
   // work, most probably time out
   int n;
   cin >> n;
   vector <int> h(n);
   vector <int> pref(n);
   for_each(h.begin(), h.end(), [&] (int &x) { cin >> x; });
   partial_sum(h.begin(), h.end(), pref.begin());

   auto sm = [&] (int x, int y) -> int {
      return pref[y] - (x ? pref[x - 1] : 0);
   };
   vector <vector <int>> dp;
   dp.assign(n, vector <int> (n, INT_MAX));
   for (int i = 0; i < n; ++i) {
      dp[i][0] = i;
   }
   const int LOG = 17;
#define T(x) (1 << (x))
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j <= i; ++j) {
         // upd dp[i][j]
         int &d = dp[i][j];
         if (j == 0) {
            d = i - j;
         }
         else {
            int kk = j - 1;
            for (int x = LOG; x >= 0; --x) {
               if (kk - T(x) + 1 >= 0 && sm(kk - T(x) + 1, j - 1) <= sm(j, i))
                  kk -= T(x);
            } // should do some pruning but still not sure for not getting TLE
            ++kk;
            for (int k = kk; k <= j - 1; ++k) {
               if (sm(k, j - 1) <= sm(j, i) && dp[j - 1][k] != INT_MAX) {
                  d = min(d, dp[j - 1][k] + (i - j));
               }
            }
         }
      }
   }
   int res = INT_MAX;
   for (int j = 0; j < n; ++j) {
      res = min(dp[n - 1][j], res);
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
