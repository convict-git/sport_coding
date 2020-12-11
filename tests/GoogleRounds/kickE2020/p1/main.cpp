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
   vector <int> ar(N);
   vector <int> diff;
   for (int i = 0; i < N; ++i) {
      cin >> ar[i];
      if (i) diff.push_back(ar[i] - ar[i - 1]);
   }
   vector <int> dp(N);
   int res = 1;
   dp[0] = 1;
   for (int i = 1; i < N - 1; ++i) {
      if (diff[i] == diff[i - 1]) {
         dp[i] = dp[i - 1] + 1;
      }
      else {
         dp[i] = 1;
      }
      res = max(res, dp[i]);
   }
   cout << res + 1 << '\n';
}

signed main()
{
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
