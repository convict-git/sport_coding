#include      <bits/stdc++.h>
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#pragma GCC   optimize ("Ofast")
#pragma GCC   optimize ("unroll-loops")
#pragma GCC   target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS   ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC  cout.precision (10); cout << fixed
#define x     first
#define y     second
#define bg(x) " [ " << #x << " : " << (x) << " ] "
#define un(x) sort(x.begin(), x.end()), \
   x.erase(unique(x.begin(), x.end()), x.end())
using   ll  = long long;
using   ull = unsigned long long;
using   ff  = long double;
using   pii = pair<int,int>;
using   pil = pair<int,ll>;
typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
   int operator()(pii x) const { return x.x*31 + x.y; }
};
gp_hash_table <pii, int, chash> mp;

#if __cplusplus > 201103L
seed_seq seq{
   (uint64_t) chrono::duration_cast<chrono::nanoseconds>
      (chrono::high_resolution_clock::now().time_since_epoch()).count(),
      (uint64_t) __builtin_ia32_rdtsc(),
      (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]
#else
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rng(seed);
#endif

#define debug(args...) { \
   /* WARNING : do NOT compile this debug func calls with following flags: // \
    * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); \
   istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) {
   it->empty(); cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
   cerr << fixed << setprecision(15)
      << " [ " <<  *it << " : " << a  << " ] "<< ' ';
   err(++it, args...);
}
/*****************************************************************************/
signed main() {
   IOS; PREC;

   auto get_sum = [&] (string &s, bool last = true) -> ll {
      int n = (int)s.size();
      vector <ll [10]> cnt(n + 2);
      vector <ll [10][2]> dp(n + 2);

      for (int d = 0; d < s[0] - '0'; ++d) {
         dp[0][d][0] = d;
         cnt[0][d] = 1;
      }
      dp[0][s[0] - '0'][1] = s[0] - '0';

      for (int i = 1; i < n; ++i) {
         int cur = s[i] - '0';
         int prv = (i > 0 ? s[i - 1] - '0' : 0);
         for (int d = 0; d <= 9; ++d) {
            for (int _d = 0; _d <= 9; ++_d) {
               dp[i][d][0] += dp[i - 1][_d][0] + cnt[i - 1][_d] * d;
               cnt[i][d] += cnt[i - 1][_d];
            }
         }

         for (int d = 0; d < cur; ++d) {
            dp[i][d][0] += dp[i - 1][prv][1] + d;
            cnt[i][d] += 1;
         }

         dp[i][cur][1] += dp[i - 1][prv][1] + cur;
      }

      ll ans = 0;
      for (int d = 0; d <= 9; ++d) {
         ans += dp[n - 1][d][0];
      }
      if (last) ans += dp[n - 1][s[n - 1] - '0'][1];
      return ans;
   };

   int tc;
   cin >> tc;
   while (tc--) {
      string a, b;
      cin >> a >> b;
      ll inc = get_sum(b);
      ll exc = get_sum(a, false);
      cout << inc - exc << '\n';
   }

   return EXIT_SUCCESS;
}
