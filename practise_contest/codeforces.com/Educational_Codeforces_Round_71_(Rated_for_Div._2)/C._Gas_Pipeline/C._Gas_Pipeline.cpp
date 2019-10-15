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

seed_seq seq{
   (uint64_t) chrono::duration_cast<chrono::nanoseconds>
      (chrono::high_resolution_clock::now().time_since_epoch()).count(),
      (uint64_t) __builtin_ia32_rdtsc(),
      (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]

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

const int N = (int)2e5 + 10;
const ll inf = 1e18;
ll dp[N][4];
int n;
ll a, b;
string s;
enum val {DOWN, MID_DOWN, MID_UP, UP};

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   while (tc--) {
      cin >> n >> a >> b;
      cin >> s;
      dp[0][DOWN] = a + 2*b;
      dp[0][MID_UP] = 2*a + 3*b;
      dp[0][MID_DOWN] = inf;
      dp[0][UP]  = inf;
      for (int i = 1; i < n; ++i) {
         if (s[i] == '0') {
            if (s[i - 1] == '0') {
               dp[i][DOWN] = min(dp[i - 1][MID_DOWN], dp[i - 1][DOWN]) + a + b;
               dp[i][MID_DOWN] = dp[i - 1][UP] + 2*a + b;
               dp[i][MID_UP] = min(dp[i - 1][MID_DOWN], dp[i - 1][DOWN]) + 2*a + 2*b;
               dp[i][UP] = min(dp[i - 1][MID_UP], dp[i - 1][UP]) + a + 2*b;
            }
            else {
               dp[i][DOWN] = inf;
               dp[i][MID_UP] = inf;
               dp[i][MID_DOWN] = dp[i - 1][UP] + 2*a + b;
               dp[i][UP] = dp[i - 1][UP] + a + 2*b;
            }
         }
         else {
            dp[i][DOWN] = inf;
            dp[i][MID_UP] = inf;
            dp[i][MID_DOWN] = inf;
            if (s[i - 1] == '0') {
               dp[i][UP] = min(dp[i - 1][UP], dp[i - 1][MID_UP]) + a + 2*b;
            }
            else {
               dp[i][UP] = dp[i  - 1][UP] + a + 2*b;
            }
         }
         for (int j = 0; j < 4; ++j) {
            if (dp[i][j] > inf) dp[i][j] = inf;
         }
      }

      cout << min(dp[n - 1][MID_DOWN], dp[n - 1][DOWN]) << "\n";
   }

   return EXIT_SUCCESS;
}
