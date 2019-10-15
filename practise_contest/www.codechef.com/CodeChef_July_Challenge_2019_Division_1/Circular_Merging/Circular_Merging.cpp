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
#define bg(x) " [ " << #x << " : " << (x) << " ] "
#define x     first
#define y     second
using   ll  = long long;
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

const int N = 805;
const ll inf = (ll)1e18;
ll dp[N][N];
ll pref[N];
int ar[N];
int n;

void solve() {
   for (int i = 0; i < 2*n; ++i)
      for (int j = 0; j < 2*n; ++j)
         dp[i][j] = inf;
   for (int i = 0; i < 2*n; ++i) {
      dp[i][i] = 0;
   }

   for (int len = 1; len < 2*n; ++len) {
      for (int i = 0; len + i < 2*n; ++i) {
         int j = len + i;
         ll cost = (pref[j] - (i > 0 ?  pref[i-1] : 0));
         for (int k = i; k < j; ++k) {
            dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + cost);
         }
      }
   }

   ll ans = inf;
   for (int i = 0; i < n; ++i) {
      int j = n + i - 1;
      ans = min(ans, dp[i][j]);
   }
   cout << ans << '\n';
}

void read() {
   cin >> n;
   for (int i = 0; i < n; ++i) {
      cin >> ar[i];
      pref[i] = ar[i] + (i > 0 ? pref[i-1] : 0);
   }
   for (int i = n; i < 2*n; ++i) {
      ar[i] = ar[i - n];
      pref[i] = pref[i-1] + ar[i];
   }
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      read(), solve();
   }

   return EXIT_SUCCESS;
}
