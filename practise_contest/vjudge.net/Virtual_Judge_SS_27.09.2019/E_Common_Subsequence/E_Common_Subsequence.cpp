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

const int N = (int)2e3 + 10;
const int Mod = (int)1e9 + 7;

int n, m;
int s[N], t[N];
int dp[N][N];
int cumm[N][N];

int add (int x, int y) {
   return (x + y) % Mod;
}
int sub (int x, int y) {
   return (x - y + Mod) % Mod;
}
int mul (int x, int y) {
   return int(1ll*x*y % Mod);
}

void solve() {
   //dp[i][j] := sets made from [0 ... i] and [0 ... j] // using s[i] and t[j]
   for (int i = 0; i <= n; ++i) {
      dp[i][0] = (s[i] == t[0]);
      cumm[i][0] = add(dp[i][0], i > 0 ? cumm[i - 1][0] : 0);
   }

   for (int j = 0; j <= m; ++j) {
      dp[0][j] = (s[0] == t[j]);
      cumm[0][j] = add(dp[0][j], j > 0 ? cumm[0][j - 1] : 0);
   }

   for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= m; ++j) {
         if (s[i] == t[j]) {
            dp[i][j] = add(1, cumm[i - 1][j - 1]);
         }
         else {
            dp[i][j] = 0;
         }
         cumm[i][j] = add(sub(add(cumm[i - 1][j], cumm[i][j - 1]) , cumm[i - 1][j - 1]), dp[i][j]);
      }
   }
   cout << dp[n][m] << '\n';
}

signed main() {
   IOS; PREC;
   cin >> n >> m;
   for (int i = 0; i < n; ++i) cin >> s[i];
   s[n] = 0;
   for (int j = 0; j < m; ++j) cin >> t[j];
   t[m] = 0;
   solve();

   return EXIT_SUCCESS;
}
