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
   // take input
   int N, K;
   cin >> N >> K;

   vector <int> F(N + 1);
   for_each(F.begin() + 1, F.end(), [&] (int &p) { cin >> p; } );
   const int fMax = *max_element(F.begin() + 1, F.end()) + 1;

   vector <vector <int>> fPrefix
      (fMax, vector <int> (N + 1));

   // compute prefix function for fvalues to calculate clashes in future
   for (int f = 0; f < fMax; ++f) {
      for (int pos = 1; pos <= N; ++pos) {
         fPrefix[f][pos] =
            (F[pos] == f) + fPrefix[f][pos - 1];
      }
   }

   // lambda function to calculate clashes
   auto getClashes = [&] (int leftIdx, int rightIdx) {
      if (rightIdx < leftIdx)
         return 0;

      int clashes = 0;
      for (int f = 0; f < fMax; ++f) {
         int occFVal = fPrefix[f][rightIdx] - fPrefix[f][leftIdx - 1];
         clashes += (occFVal > 1 ? occFVal : 0);
      }
      return clashes;
   };

   // initiate dp with base values
   // dp[i] : for the prefix [1....i] what's the min cost
   vector <int> dp(N + 1, INT_MAX);
   dp[0] = 0;

   // calculate dp
   for (int pos = 1; pos <= N; ++pos) {
      for (int prvPos = 0; prvPos < pos; ++prvPos) {
         int clashes = getClashes(prvPos + 1, pos);

         // dp for a current pos,  comes from a prev prvPos, with
         // cost a new table and clashes on this new table
         dp[pos] = min(dp[pos],
               dp[prvPos] + K + clashes);
      }
   }

   // finalt result is cost for the whole prefix i.e. [1...N]
   cout << dp[N] << '\n';
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
