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

void preproc()
{
}

void solve()
{
   int N, M;
   cin >> N >> M;
   vector <long long> dp(N + 2);

   while (M--) {
      int l, r, k;
      cin >> l >> r >> k;
      dp[l] += k;
      dp[r + 1] -= k;
   }

   long long res = 0;
   for (int i = 1; i < N + 2; ++i) {
      dp[i] += dp[i - 1];
      res = max(res, dp[i]);
   }
   cout << res << '\n';
}

signed main()
{
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
