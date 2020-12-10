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


const int Maxn = 4e3+10;
int dp[Maxn], ar[3];
int N;
void preproc()
{
}

void solve()
{
   cin >> N;
   for (int i = 0; i < 3; ++i) cin >> ar[i];

   memset(dp, 0, sizeof(dp));
   for (int i = 1; i <= N; ++i) {
      int mx = 0;
      for (int j = 0; j < 3; ++j) {
         if (i >= ar[j] and (dp[i - ar[j]] != 0 or i - ar[j] == 0)) {
            mx = max(mx, dp[i - ar[j]] + 1);
         }
      }
      dp[i] = mx;
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
