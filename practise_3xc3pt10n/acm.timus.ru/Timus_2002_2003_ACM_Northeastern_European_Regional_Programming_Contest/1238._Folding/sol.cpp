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

// reo[pos][len] -> how many repitions [pos..pos+len-1] from pos
// dp[pos][len] -> {min string len required to show string from (pos..pos+len-1), parent}
int rep[Maxn][Maxn];
pair <int, int> dp[Maxn][Maxn];
int N;
string s;

void preproc()
{
}

void solve()
{
   cin >> s;
   N = (int)s.size();

   // calculate rep
   memset(rep, 0, sizeof(rep));
   for (int len = 1; len <= N; ++len) {
      for (int pos = N - 1; pos >= 0; --pos) { // working on suffixes
         if (pos + len - 1 >= N)
            continue;
         rep[pos][len] = 1;
         if (pos + 2*len - 1 <= N - 1 and
               s.substr(pos, len) == s.substr(pos + len, len))
         {
            rep[pos][len] += rep[pos + len][len];
         }
      }
   }

   auto dig = [&] (int x) -> int {
      int res = 0;
      while (x) ++res, x /= 10;
      return res; };

   // calculate dp
   // base case
   for (int pos = 0; pos < N; ++pos) {
      dp[pos][1] = make_pair(1, pos);
   }

   for (int len = 2; len <= N; ++len) { // increasing length
      for (int pos = 0; pos < N; ++pos) {
         dp[pos][len] = make_pair(INT_MAX, INT_MAX);
         // choose some mid, mid in [pos + 1, pos+len-1],
         // parition into s[pos.. mid-1] and s[mid.. pos + len - 1]
         for (int mid = pos + 1; mid <= pos + len - 1; ++mid) {
            auto join = make_pair(dp[pos][mid - pos].first +
                  dp[mid][len - (mid - pos)].first, mid);
            dp[pos][len] = min(dp[pos][len], join);
         }

         // compress the string and go deeper
         for (int k = 1; 2 * k <= len; ++k) {
            if (len % k == 0 and
                  k * min(len / k, rep[pos][k]) == len)  // can be partitioned
            {
               auto comp = make_pair(2 + dig(min(len / k, rep[pos][k]))
                     + dp[pos][k].first, -1 * k);
               dp[pos][len] = min(dp[pos][len], comp);
            }
         }
      }
   }


   // preorder traversal
   function <void(int, int)> pre_order = [&] (int pos, int len) -> void {
      if (len == 1) {
         cout << s[pos];
         return;
      }

      auto sol = dp[pos][len];
      if (sol.second < 0) { // repitition string
         int sub_len = -1*sol.second;
         cout << len / sub_len << "(";
         pre_order(pos, sub_len);
         cout << ")";
         return;
      }
      else { // break into two
         int mid = sol.second;
         pre_order(pos, mid - pos);
         pre_order(mid, len - (mid - pos));
         return;
      }
   };

   pre_order(0, N);
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
