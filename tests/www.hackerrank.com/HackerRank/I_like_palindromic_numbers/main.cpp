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

const int mxn = 1e5+1;
int dp[2*mxn+1][21][21];
void solve() {
   // calculate all palindrome
   vector <long long> pal;
   for (int i = 0; i <= mxn; ++i) {
      string s = to_string(i), rve = s;
      reverse(rve.begin(), rve.end());
      pal.push_back(stoll(s + rve));
      if (i) {
         string rvo = s.substr(0, (int)s.size()-1);
         reverse(rvo.begin(), rvo.end());
         pal.push_back(stoll(s + rvo));
      }
   }
   sort(pal.begin(), pal.end());
   // debug(pal.size(), 2*mxn+1);

   // count for eq class
   memset(dp, 0, sizeof(dp));
   for (int pos = 0; pos < 2*mxn-1; ++pos) {
      for (int dv = 1; dv <= 20; ++dv) {
         ++dp[pos][dv][pal[pos] % dv];
         for (int rm = 0; pos > 0 && rm < dv; ++rm) {
            dp[pos][dv][rm] += dp[pos-1][dv][rm];
         }
      }
   }

   // solve queries
   int q;
   cin >> q;
   while (q--) {
      long long n, m;
      int k;
      cin >> n >> m >> k;
      int idx = int(upper_bound(pal.begin(), pal.end(), m) - pal.begin());
      cout << dp[idx-1][k][(-1ll * (n % k) + k) % k] << '\n';
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
