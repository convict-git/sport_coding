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
   string s;
   cin >> s;
   int N = (int)s.size();
   int M;
   cin >> M;
   vector <int> dp(N + 1);
   while (M--) {
      int ai;
      cin >> ai;
      int L = ai - 1, R = N - ai + 1 - 1;
      debug(L, R);
      ++dp[L];
      --dp[R + 1];
   }

   for (int i = 0; i < N; ++i) {
      dp[i + 1] += dp[i];
   }

   debug(dp);
   for (int i = 0; i < N/2; ++i) {
      if (dp[i] % 2 == 0) { // nochange
      }
      else {
         swap(s[i], s[N - i - 1]);
      }
   }
   cout << s << '\n';
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
