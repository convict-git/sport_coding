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
   int n, k;
   string s;
   cin >> n >> k >> s;
   const int N = 1004;
   bool dp[N][2 * N];
   int pi[N][2 * N];

   for (int i = 0; i <= n; ++i) {
      for (int diff = 0; diff <= 2 * n; ++diff) {
         dp[i][diff] = false;
      }
   }

   int OFF = 1001;
   dp[0][OFF] = true;
   pi[0][OFF] = -1;

   for (int i = 0; i < n; ++i) {
      for (int diff = -k + 1; diff < k; ++diff) {
         // dp[i][OFF + diff] is an intermediate state, do not allow
         // diff to be greater than equal to k or less than equal to -k

         if (dp[i][OFF + diff] == false) {
            continue;
         }

         if (s[i] == 'W' || s[i] == '?') {
            dp[i + 1][OFF + diff + 1] = true;
            pi[i + 1][OFF + diff + 1] = 1;
         }
         if (s[i] == 'D' || s[i] == '?') {
            dp[i + 1][OFF + diff] = true;
            pi[i + 1][OFF + diff] = 0;
         }
         if (s[i] == 'L' || s[i] == '?') {
            dp[i + 1][OFF + diff - 1] = true;
            pi[i + 1][OFF + diff - 1] = -1;
         }
      }
   }

   if (dp[n][OFF - k] || dp[n][OFF + k]) {
      string ans = "";
      int pos = n, diff = (dp[n][OFF- k] ? OFF - k : OFF + k);
      while (pos >= 1) {
         if (pi[pos][diff] == 1) {
            ans = 'W' + ans;
            diff -= 1;
         }
         else if (pi[pos][diff] == 0) {
            ans = 'D' + ans;
            diff -= 0;
         }
         else {
            ans = 'L' + ans;
            diff += 1;
         }
         pos -= 1;
      }
      cout << ans << '\n';
   }
   else cout << "NO\n";

   return EXIT_SUCCESS;
}
