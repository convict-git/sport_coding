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

vector <int> pref_func (string &s) { // O(|s|)
  int n = (int)s.size();
  vector <int> pi(n);
   pi[0] = 0;
   int sz = (int)s.size();
   for (int i = 1; i < sz; ++i) {
      int len_j = pi[i-1];
      int j = len_j - 1;
      while (len_j > 0 && s[j + 1] != s[i]) {
         len_j = pi[j];
         j = len_j - 1;
      }
      if (s[len_j] == s[i])
         ++len_j;
      pi[i] = len_j;
   }
   return pi;
}

void solve()
{
   int N, Q;
   cin >> N >> Q;
   string s;
   cin >> s;
   vector <pair <int, int>> queries(Q);
   for (int i = 0; i < Q; ++i) {
      cin >> queries[i].first >> queries[i].second;
   }

   for (auto p : queries) {
      int l = p.first, r = p.second;
      --l, --r;
      int m = r - l + 1;
      vector <vector <int>> dp(N + 1, vector <int> (m + 1));
      for (int i = 0; i <= N; ++i) {
         dp[i][0] = 1;
      }
      for (int i = 1; i <= N; ++i) {
         for (int j = 1; j <= m; ++j) {
            if (s[i - 1] == s[l + j - 1]) {
               dp[i][j] += dp[i - 1][j - 1];
            }
            dp[i][j] += dp[i - 1][j];
         }
      }
      int subsqOcc = dp[N][m];

      int occ = 0;
      string tmp = s.substr(l, m) + '#' + s;
      vector <int> pi = pref_func(tmp);
      for (int i = m; i < m + 1 + N; ++i) {
         if (pi[i] == m) { ++occ; }
      }

      // debug(l, r, subsqOcc, occ);
      if (subsqOcc - occ >= 1) { cout << "YES\n"; }
      else { cout << "NO\n"; }
   }
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
