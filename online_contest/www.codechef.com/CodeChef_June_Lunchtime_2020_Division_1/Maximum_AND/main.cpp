#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#define ms(x,y,n) for(int i = 0; i < n; ++i) x[i] = y;
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

void preproc() {
}

void solve() {
   int N, K;
   cin >> N >> K;
   vector <int> bitCnt(32);
   for (int i = 0; i < N; ++i) {
      int ai; cin >> ai;

      for (int d = 0; d <= 31; ++d) {
         if (ai & (1 << d)) {
            bitCnt[d] += 1;
         }
      }
   }

   long long dp[33][K+1];
   memset(dp, 0ll, sizeof(dp));

   for (int d = 1; d <= 32; ++d) {
      for (int k = 1; k <= K; ++k) {
         if (k <= d) {
            long long notTake = dp[d - 1][k];
            long long take = dp[d - 1][k - 1];
            dp[d][k] = max(take + 1ll * bitCnt[d] * (1 << (d-1)), notTake);
         }
      }
   }
   long long res = dp[31][K];
   cout << res << '\n';
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
