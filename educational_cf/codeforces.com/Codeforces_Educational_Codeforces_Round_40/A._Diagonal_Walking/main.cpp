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
   int N;
   cin >> N;
   string s;
   cin >> s;
   s = '#' + s;

   int dp[N + 1];
   for (int i = 0; i <= N; ++i) {
      dp[i] = i;
   }

   for (int i = 2; i <= N; ++i) {
      if (s[i] != s[i - 1]) { // use pair last one
         dp[i] = min(dp[i], dp[i - 2] + 1);
      }
      dp[i] = min(dp[i - 1] + 1, dp[i]);
   }
   cout << dp[N] << '\n';
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
