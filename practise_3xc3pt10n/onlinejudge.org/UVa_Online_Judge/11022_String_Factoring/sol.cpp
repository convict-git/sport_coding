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

const int Maxn = 200;

int N;
string s;
int dp[Maxn][Maxn]; // dp[pos][len] -> min value of lenth required to show s[pos,...pos + len - 1]
int rep[Maxn][Maxn]; // rep[pos][len] -> count of repitiotion from pos of length len

void preproc()
{
}

void solve()
{
   N = (int)s.size();

   // preprocessing rep
   memset(rep, 0, sizeof(rep));
   for (int len = 1; len <= N; ++len) {
      for (int pos = N - 1; pos >= 0; --pos) { // dag comes from suffix, hence opp order
         if (pos + len - 1 >= N)
            continue;

         rep[pos][len] = 1;

         if (pos + 2*len - 1 <= N - 1) {
            // calc rep[pos][len]
            // s[pos..pos + len - 1] == s[pos + len ... pos + 2*len - 1]
            // rep[pos][len] += rep[pos + len][len]
            bool is_same = true;
            for (int k = 0; k < len; ++k) {
               if (s[pos + k] != s[pos + len + k]) {
                  is_same = false;
               }
            }
            if (is_same) {
               rep[pos][len] += rep[pos + len][len];
            }
         }
      }
   }

   // calculate dp
   for (int pos = 0; pos < N; ++pos) {
      dp[pos][1] = 1;
   }
   for (int len = 2; len <= N; ++len) {
      for (int pos = 0; pos < N; ++pos) {
         dp[pos][len] = INT_MAX;
         // case I <- join
         for (int mid = pos + 1; mid <= pos + len - 1; ++mid) {
            dp[pos][len] = min(dp[pos][len],
                  dp[pos][mid - pos] + dp[mid][len - (mid - pos)]);
         }
         // case II <- compress
         for (int sub_len = 1; 2 * sub_len <= len; ++sub_len) {
            if (sub_len * min(len/sub_len, rep[pos][sub_len]) == len) {
               dp[pos][len] = min(dp[pos][len], dp[pos][sub_len]);
            }
         }
      }
   }

   cout << dp[0][N] << '\n';
}

signed main()
{
   IOS; PREC;
   preproc();

   int tc = 1;
   // cin >> tc;
   for (int Tt = 1; Tt <= tc; ++Tt) {
      // cout << "Case #" << Tt << ": ";
      while (cin >> s, s != "*")
         solve();
   }
   return EXIT_SUCCESS;
}
