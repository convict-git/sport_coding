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

string s;
vector <vector <pair <int, string>>> dp;

int comp_len (int pos, int len) { // O(|s|)
   int sz = len;
   vector <int> pi(sz);
   for (int i = 1; i < sz; ++i) {
      int len_j = pi[i-1];
      int j = len_j - 1;
      while (len_j > 0 && s[pos + j + 1] != s[pos + i]) {
         len_j = pi[j];
         j = len_j - 1;
      }
      if (s[pos + len_j] == s[pos + i])
         ++len_j;
      pi[i] = len_j;
   }
   int k = sz - pi[sz - 1];
   return (sz % k ? sz : k);
}

pair <int, string> get (int, int);
pair <int, string> rec (int ,int);

// dp[L][R] := final res of how substring s[i...j] will look like when all the actions
// are performed
//

pair <int, string> get (int l_idx, int r_idx) {
   debug("get", l_idx, r_idx, s.substr(l_idx, r_idx - l_idx + 1));
   if (dp[l_idx][r_idx] != make_pair(INT_MAX, to_string(' '))) {
      return dp[l_idx][r_idx];
   }
   int N_sub = r_idx - l_idx + 1;
   int comp_len_var = comp_len(l_idx, N_sub);
   string res;
   if (comp_len_var == N_sub) {
      res = rec(l_idx, r_idx).second;
   }
   else {
      int K = N_sub / comp_len_var;
      res = to_string(K) + '(' + rec(l_idx, l_idx + comp_len_var - 1).second + ')';
   }
   return make_pair(res.size(), res);
}

pair <int, string> rec (int l_idx, int r_idx) {
   debug("rec", l_idx, r_idx, s.substr(l_idx, r_idx - l_idx + 1));
   if (dp[l_idx][r_idx] != make_pair(INT_MAX, to_string(' '))) {
      return dp[l_idx][r_idx];
   }
   if (l_idx == r_idx) {
      return make_pair(1, to_string(s[l_idx]));
   }

   // doing it for l_idx and r_idx
   // dp[l_idx][r_idx] <- dp[l_idx][mid-1] ... dp[mid..r_idx]
   for (int mid = l_idx; mid <= r_idx; ++mid) {
      auto lst_dp = (mid - 1 >= l_idx ?
            rec(l_idx, mid - 1) : make_pair(0, to_string(' ')));

   }

   return dp[l_idx][r_idx];
}

void preproc()
{
}

void solve()
{
   // give a substring, returns the compression length
   // dp[i] -> in each recursion of a substring,
   cin >> s;
   int N = (int)s.size();
   dp.assign(N, vector <pair <int, string>> (N, make_pair(INT_MAX, to_string(' '))));
   cout << rec(0, N - 1).second << '\n';
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
