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

#define T(x) (1 << (x))
void solve() {
   // dp[i][k] : break the prefix [0 ... i] in atleast k segment, what's the min
   // height of the last segment
   // dp[j][k + 1] <- from segment [i+1, j], dp[i][k] which k greatest such that
   // dp[i][k] <= s[i+1, j]
   //
   // dp[j][k] = min(dp[j][k + 1], dp[j][k]);
   // forward updates
   int n;
   cin >> n;
   vector <int> h(n);
   vector <int> pref(n);

   for_each(h.begin(), h.end(), [&] (int &x) {cin >> x;});
   partial_sum(h.begin(), h.end(), pref.begin());

   auto sm = [&] (int x, int y) -> int { // sum[x, y]
      return pref[y] - (x ? pref[x - 1] : 0);
   };

   const int LOG = 17;
   vector <vector <int>> dp;
   dp.assign(n, vector <int> (n+1, INT_MAX));

   for (int pos = 0; pos < n; ++pos) { // base case
      dp[pos][0] = 0;
   }
   dp[0][1] = h[0];

   for (int pos = 0; pos < n; ++pos) { // upd bottom up
      for (int k = n - 1; k >= 0; --k) {
         dp[pos][k] = min(dp[pos][k], dp[pos][k + 1]);
      }
      for (int nxt = pos + 1; nxt < n; ++nxt) {
         int s = sm(pos + 1, nxt);
         int k = 0;
         for (int d = LOG; d >= 0; --d) {
            if (k + T(d) - 1 <= n && dp[pos][k + T(d) - 1] <= s) {
               k += T(d);
            }
         }
         --k;
         dp[nxt][k + 1] = min(dp[nxt][k + 1], s);
      }
   }

   int res = 0;
   for (int k = n; k >= 0; --k) {
      if (dp[n-1][k] != INT_MAX) {
         res = n - k;
         break;
      }
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
