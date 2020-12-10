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
   vector <int> ar(N + 1);
   for (int i = 1; i <= N; ++i) {
      cin >> ar[i];
   }

   vector <vector <int>> dp(N + 1, vector <int> (2, INT_MAX));
   // dp[i][false] := friend kills at i and is the first
   // dp[i][true] := friends kill at i and is the second

   dp[0][0] = 0;
   for (int i = 1; i <= N; ++i) {
      dp[i][false] = min({
            i - 2 >= 0 ? min(dp[i - 2][false], dp[i - 2][true]) : INT_MAX,
            i - 3 >= 0 ? min(dp[i - 3][false], dp[i - 3][true) : INT_MAX
            })
      + (ar[i] == 1); // uses

      dp[i][false] = min({
            i - 2 >= 0 ? min(dp[i - 2][false], dp[i - 2][true]) : INT_MAX,
            i - 3 >= 0 ? min(dp[i - 3][false], dp[i - 3][true) : INT_MAX
            })
      // 0 1 1 0 0 1 1
   }

}

signed main()
{
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
