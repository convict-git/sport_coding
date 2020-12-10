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
   vector <long long> ar(N);
   for (long long &a : ar) cin >> a;

   vector<vector <long long>> max_dp(N, vector <long long> (6, LLONG_MIN));
   vector<vector <long long>> min_dp(N, vector <long long> (6, LLONG_MAX));

   for (int i = 0; i < N; ++i) {
      min_dp[i][0] = max_dp[i][0] = 1;
   }

   max_dp[0][1] = ar[0];
   min_dp[0][1] = ar[0];

   for (int i = 1; i < N; ++i) {
      for (int x = 1; x <= 5; ++x) {
         if (i >= x - 1) { // feasible
            max_dp[i][x] = max({ar[i] * max_dp[i - 1][x - 1],
                  ar[i] * min_dp[i - 1][x - 1],
                  max_dp[i - 1][x]});

            min_dp[i][x] = min({ar[i] * min_dp[i - 1][x - 1],
                  min_dp[i - 1][x],
                  ar[i] * max_dp[i - 1][x - 1]});
         }
      }
   }

   cout << max_dp[N - 1][5] << '\n';
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
