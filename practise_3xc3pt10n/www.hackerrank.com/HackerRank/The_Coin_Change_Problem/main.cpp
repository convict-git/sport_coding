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
   vector <int> Coin(M);
   for (int& c : Coin) cin >> c;

   sort(Coin.begin(), Coin.end(), greater <int> ());

   vector <long long> dp(N + 1);

   dp[0] = 1ll;

   for (int c : Coin) { // try all
      for (int i = 0; i <= N; ++i) {
         if (i - c >= 0 and dp[i - c] != 0) {
            dp[i] += dp[i - c];
         }
      }
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
