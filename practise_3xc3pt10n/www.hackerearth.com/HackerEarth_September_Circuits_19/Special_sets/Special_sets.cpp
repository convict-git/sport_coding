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
   int operator () (pii x) const { return x.x*31 + x.y; }
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
//Don’t practice until you get it right. Practice until you can’t get it wrong

const int Mod = (int)1e9 + 7;
inline int add (int x, int y) {
   return (x + y) % Mod;
}
inline int mul (int x, int y) {
   return int(1ll*x*y % Mod);
}

signed main() {
   IOS; PREC;
   // dp[i][x] := no. of ordered sets such that the length is i and contains max as x
   //
   // dp(i, x) <- dp(i - 1, x - 2), dp(i - 1, x - 3), ....
   // dp (i, x) while contain values 1 ... x satisfying the condition
   // when adding (i + 1)th element as x, we can use previous answers from x - 2, ... 1 of
   // i length and keep x at i + 1 positions
   // dp[i][x] := i * (dp[i - 1][1] + dp[i - 1][2] + .... + dp[i - 1][x - 2])

   int n;
   cin >> n;
   vector <vector <int>> dp(n + 1, vector <int>(n + 1));

   for (int x = 1; x <= n; ++x) { // base case
      dp[1][x] = 1;
   }

   vector <int> pref(n + 1);

   for (int i = 2; i <= n; ++i) {
      for (int x = 1; x <= n; ++x) { // calc prefix
         pref[x] = add(dp[i - 1][x], (x > 1 ? pref[x - 1] : 0));
      }
      for (int x = i + 1; x <= n; ++x) { // update dp table
         dp[i][x] = mul(i, pref[x - 2]);
      }
   }

   int ans = 0;
   for (int i = 1; i <= n; ++i) {
      for (int x = 1; x <= n; ++x) {
         ans = add(dp[i][x], ans);
      }
   }
   cout << ans << '\n';

   return EXIT_SUCCESS;
}
