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

void preproc() {
}

void solve() {
   int n, K, V;
   cin >> n >> K >> V;
   vector <int> ar(n);
   vector <int> rem(n);
   int sm_whole  = 0, rm_whole = 0;
   for (int i = 0; i < n; ++i) {
      cin >> ar[i];
      rem[i] = ar[i] % K;
      rm_whole += rem[i];
      ar[i] -= rem[i];
      sm_whole += ar[i];
   }
   debug(ar);
   debug(rem);
   int Vrem = V - min(V, sm_whole);
   // get Vrem from rem array ?
   if (Vrem > rm_whole) {
      cout << "NO\n";
   }
   vector <bool> dp(rm_whole+1);
   dp[0] = true;
   for (int i = 0; i < n; ++i) {
   }
}

signed main() {
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
