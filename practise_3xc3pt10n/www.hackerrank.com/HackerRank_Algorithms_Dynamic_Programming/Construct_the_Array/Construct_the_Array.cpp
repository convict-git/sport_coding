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

const int Mod = (int)1e9 + 7;
inline int add (int x, int y) {
   return (x + y) % Mod;
}
inline int mul (int x, int y) {
   return int(1ll * x * y % Mod);
}
inline int sub (int x, int y) {
   return (x - y + Mod) % Mod;
}

signed main() {
   IOS; PREC;
   int n, k, x;
   cin >> n >> k >> x;
   int dp[2][2];
   dp[0][0] = 1, dp[0][1] = 0;

   // except 1, other values of k should not be differentiated with each other
   // hence if total[i][k] := starting from 1 and ending at k at ith index,
   // then total[i][1] != total[i][2] = total[i][3] = ... = total[i][k]

   for (int i = 1; i < n; ++i) {
      int j = i & 1;
      dp[j][0] = mul(k - 1, dp[!j][1]);
      dp[j][1] = add(dp[!j][0], mul(k - 2, dp[!j][1]));
   }

   cout << (x == 1 ? dp[(n - 1) & 1][0] : dp[(n - 1) & 1][1]) << '\n';

   /*
   // let convert into shit unreadable code

   int dp[4];
   dp[0] = 1, dp[1] = 0;

   for (int i = 1; i < n; ++i) {
      int j = (i & 1) << 1, j_ = (!j) << 1;
      dp[j] = 1ll * (k - 1) * dp[-(~j_)] % Mod ;
      dp[-(~j)] = (dp[j_] +  1ll * (k - 2) * dp[-(~j_)] % Mod) % Mod;
   }
   n = (n - 1) & 1;
   cout << (x == 1 ? dp[n << 1] : dp[(n << 1) + 1]) << '\n';
   */

   /*
   // commented code solves -> subtask n * k < 1e7
   const int N = 1003, K = 102;
   int dp[N][K];
   for (int j = 0; j <= k; ++j)
      dp[0][j] = 0;

   dp[0][1] = 1;
   int cumm[K];
   for (int j = 1; j <= k; ++j) {
      cumm[j] = add(dp[0][j], (j ? cumm[j - 1] : 0));
   }

   auto give = [&] (int i, int j) -> int {
      if (i > j) return 0;
      return sub((j >= 0 ? cumm[j] : 0), (i ? cumm[i - 1] : 0));
   };

   // dp[i][j] = dp[i - 1][0...j - 1] + dp[i - 1][j + 1 ... k]
   for (int i = 1; i < n; ++i) {
      for (int j = 1; j <= k; ++j) {
         dp[i][j] = add(give(1, j - 1), give(j + 1, k));
         cerr << dp[i][j] << ' ';
      }
      for (int j = 1; j <= k; ++j) {
         cumm[j] = add(dp[i][j], (j ? cumm[j - 1] : 0));
      }
      cerr << '\n';
   }
   cout << dp[n - 1][x] << '\n';
   */


   return EXIT_SUCCESS;
}
