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
   const int Maxn = 510;
   vector <vector <long long>> dp;
   dp.assign(Maxn, vector <long long> (Maxn));
   // Think of this partioting numbers
   // dp[n][h] -> no. of ways to make 'n' using some numbers such that the
   // max number used is h
   //
   // dp[n][h][w] -> no. of ways to make 'n' using exactly w numbers such that
   // max of them is h, it leads to overcounting, that means you can actually
   // drop some state (reduce the space or merge equivalence classes to create a
   // bigger equivalence class).
   // dp[n][h][w] -> dp[n][h], don't care how many numbers are used

   dp[1][1] = 1;
   for (int i = 2; i <= N; ++i) {
      for (int k = 1; i - k >= 0; ++k) {
            dp[i][k] = dp[i - 1][k - 1] + dp[i - k][k - 1];
      }
   }

   long long res = 0;
   for (int k = 1; k <= N; ++k) {
      res += dp[N][k];
   }
   cout << res - 1 << '\n';

   return;
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
