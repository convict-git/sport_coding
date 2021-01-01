#include      <bits/stdc++.h>
#pragma GCC       optimize ("Ofast")
#pragma GCC       optimize ("unroll-loops") /* can make things slower */
#pragma GCC       target   ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC       optimize ("-ffloat-store")
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
   // take input
   const int Mod = (int)1e9 + 7;
   int n, x;
   cin >> n >> x;
   vector <int> coins(n);
   for (int& c : coins) cin >> c;

   vector <int> dp(x + 1);
   dp[0] = 1; // base case, no of ways to get nothing is 1 (yeah!!)
   for (int c : coins)
      for (int v = 0; v + c <= x; ++v)
         dp[v + c] = (dp[v] + dp[v + c]) % Mod; // update
   cout << dp[x] << '\n';
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

