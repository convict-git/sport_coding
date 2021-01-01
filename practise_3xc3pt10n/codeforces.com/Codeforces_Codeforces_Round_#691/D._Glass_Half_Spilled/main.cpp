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
#warning No preprocessing done
}

void reset()
{
#warning No resetting of global variables done
}

void solve()
{
   int N;
   cin >> N;
   vector <int> capacity(N), value(N);
   for (int i = 0; i < N; ++i) {
      cin >> capacity[i] >> value[i];
   }
   int totalCap = accumulate(capacity.begin(), capacity.end(), 0);
   long double totalVal = accumulate(value.begin(), value.end(), 0);

   const long double infi = 1e18;
   const long double eps = 1e-9;
   long double dp[N + 1][totalCap + 1][2];
   for (int k = 0; k <= N; ++k) {
      for (int x = 0; x <= totalCap; ++x) {
         for (int i : {0, 1}) {
            dp[k][x][i] = -infi;
         }
      }
   }

   dp[0][0][0] = 0, dp[0][0][1] = 0; // this is the base case

   // the recursion
   // (1.. i, k, cap) <- (1..i-1, k, cap) or (1...i-1, k-1, cap - capAr[i-1]) + value[i]

   for (int i = 1; i <= N; ++i) {
      for (int k = 1; k <= N; ++k) {
         for (int cap = 0; cap <= totalCap; ++cap) {
            dp[k][cap][i & 1] = dp[k][cap][!(i & 1)];
            if (cap - capacity[i - 1] >= 0 and
                  fabs(infi + dp[k - 1][cap - capacity[i - 1]][!(i & 1)]) > eps)
            {
               dp[k][cap][i & 1] =
                  max(
                        dp[k][cap][i & 1],
                        dp[k - 1][cap - capacity[i - 1]][!(i & 1)] + value[i - 1]
                     );
            }
         }
      }
   }

   for (int k = 1; k <= N; ++k) {
      long double res = 0;
      for (int cap = 0; cap <= totalCap; ++cap) {
         if (fabs(infi + dp[k][cap][N & 1]) > eps) {
            res =
               max(
                     res,
                     min(
                        (long double)cap,
                        dp[k][cap][N & 1] / 2 + totalVal / 2
                        )
                  );
         }
      }
      cout << res << ' ';
   }
   cout << '\n';
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
      reset();
      solve();
   }
   return EXIT_SUCCESS;
}
