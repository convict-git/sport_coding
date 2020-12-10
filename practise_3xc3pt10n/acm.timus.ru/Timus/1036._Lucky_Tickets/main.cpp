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
std::string toString(__int128 num) {
    std::string str;
    do {
        int digit = num % 10;
        str = std::to_string(digit) + str;
        num = (num - digit) / 10;
    } while (num != 0);
    return str;
}

void solve()
{
   // number has 2 * N digits, sum(1...N) = sum(N + 1...2*N)
   // sum(1...2*N) = S
   // t = dp[N][S / 2] -> number of ways ?
   // answer is just square of it right? t * t
   // dp[i][s] -- using digit d ---> dp[i + 1][s + d]
   int N, S;
   cin >> N >> S;
   if (S % 2 == 1) { // edge case when S is odd, which is not possible
      cout << 0 << '\n';
      return;
   }
   vector<vector <__int128_t>> dp(N + 1, vector <__int128_t> (S + 1));
   dp[0][0] = 1;

   for (int i = 1; i <= N; ++i) { // 50
      for (int s = 0; s <= S; ++s) { // 1000
         for (int d = 0; d <= 9; ++d) { // 10
            if (s - d >= 0)
               dp[i][s] += dp[i - 1][s - d];
         }
      }
   }
   cout << toString(dp[N][S/2]*dp[N][S/2]) << '\n';
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
