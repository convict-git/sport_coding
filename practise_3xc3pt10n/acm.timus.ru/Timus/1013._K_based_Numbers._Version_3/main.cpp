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

long long N, K, M;

void preproc()
{
}

long long binexp (long long y) {
   // 60 operations
   vector <long long> mat {K-1, 1, K-1, 0};
   vector <long long> res {1, 0, 0, 1};
   vector <long long> tmp {0, 0, 0, 0};

   while (y) {
      if (y & 1ll) {
         // res = res * mat
         tmp[0] = res[0] * mat[0] + res[1] * mat[2];
         tmp[1] = res[0] * mat[1] + res[1] * mat[3];
         tmp[2] = res[2] * mat[0] + res[3] * mat[2];
         tmp[3] = res[2] * mat[1] + res[3] * mat[3];
         for (int i = 0; i < 4; ++i) {
            res[i] = tmp[i] % M;
         }
      }

      tmp[0] = mat[0] * mat[0] + mat[1] * mat[2];
      tmp[1] = mat[0] * mat[1] + mat[1] * mat[3];
      tmp[2] = mat[2] * mat[0] + mat[3] * mat[2];
      tmp[3] = mat[2] * mat[1] + mat[3] * mat[3];
      for (int i = 0; i < 4; ++i) {
         mat[i] = tmp[i] % M;
      }
      // mat = mat * mat
      y >>= 1ll;
   }
   return (K-1) * (res[0] + res[1]) % M;
}

void solve()
{
   cin >> N >> K >> M;
   // no two succcessive zereos
   // [0] -> 1..9
   // [1...N - 1] -> 0..9 No two successive zeroes
   // dp[i][digit] := no of k-based number with no two successive zeroes till 0...i
   // if d > 0 -> dp[i][d] = dp[i - 1][0] + .... + dp[i - 1][9]
   // else dp[i][0] = dp[i - 1][1] + ... + dp[i - 1][9]
   //
   // dp[i][true] = 9 * (dp[i - 1][true] + dp[i - 1][false])
   // dp[i][false] = dp[i - 1][true]
   //
   //// [ ti fi ] = [ti-1 fi-1] [9  1 ]
   //                           [9  0 ]

   // tn fn = [9 0] *  [ 9 1 ] ** n
   //                   [ 9 0 ]
   //
   cout << binexp(N - 1) << '\n';
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
