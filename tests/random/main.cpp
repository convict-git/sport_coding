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

   if (M < N) {
      cout << -1 << '\n';
      return;
   }

   vector <vector <int>> div(M - N + 2, vector <int> ());

   for (int i = 2; i <= M; ++i) {
      for (int j = 0; j <= M; j += i) {
         // j is multiple of i,
         if (j >= N) {
            div[j - N].push_back(i);
         }
      }
   }

   vector <int> dp(M - N + 2, INT_MAX);
   dp[0] = 0;

   for (int i = N; i <= M; ++i) {
      for (int x : div[i - N]) {
         if (x % 2 != 0 or x == i) continue;
         if (i + x - N <= M - N and dp[i - N] != INT_MAX) {
            dp[i + x - N] = min(dp[i + x - N], dp[i - N] + (i / x));
         }
      }
   }

   int res = dp[M - N];

   cout << (res == INT_MAX ? -1 : res) << '\n';
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
