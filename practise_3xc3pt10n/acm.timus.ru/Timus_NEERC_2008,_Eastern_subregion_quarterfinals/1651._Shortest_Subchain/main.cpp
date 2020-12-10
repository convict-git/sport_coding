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
   int sz;
   cin >> sz;
   vector <int> chain(sz);
   for (int i = 0; i < sz; ++i) {
      cin >> chain[i];
   }
   int mxv = *max_element(chain.begin(), chain.end());

   vector <int> dp(mxv + 1, INT_MAX);
   vector <int> pi(sz);
   vector <int> lst(mxv + 1, -1);
   iota(pi.begin(), pi.end(), 0);
   int prv = 0;
   dp[prv] = 0;
   for (int i = 0; i < sz; ++i) {
      if (dp[chain[i]] > dp[prv] + 1) {
         dp[chain[i]] = dp[prv] + 1;
      }
      else {
         pi[i] = pi[lst[chain[i]]];
      }
      lst[chain[i]] = i;
      prv = chain[i];
   }
   debug(dp);

   vector <int> res;
   for (int i = sz - 1; i >= 0; ) {
      if (pi[i] == i) {
         res.push_back(chain[i]);
         i -= 1;
      }
      else {
         i = pi[i];
      }
   }

   reverse(res.begin(), res.end());
   for (int v : res) { cout << v << ' '; }
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
    solve();
  }
  return EXIT_SUCCESS;
}
