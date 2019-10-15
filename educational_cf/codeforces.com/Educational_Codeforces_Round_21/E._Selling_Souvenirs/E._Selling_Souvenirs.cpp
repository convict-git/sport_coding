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
   int n, m;
   cin >> n >> m;
   vector <int> one, two, three;
   int n1, n2, n3;

   for (int i = 0; i < n; ++i) {
      int wi, ci;
      cin >> wi >> ci;
      if (wi == 1) one.push_back(ci);
      else if (wi == 2) two.push_back(ci);
      else three.push_back(ci);
   }
   n1 = (int)one.size(), n2 = (int)two.size(), n3 = (int)three.size();

   sort (one.begin(), one.end(), greater <int>());
   sort (two.begin(), two.end(), greater <int>());
   sort (three.begin(), three.end(), greater <int>());

   vector <ll> pref(n3);

   for (int i = 0; i < n3; ++i) {
      pref[i] = 1ll * three[i] + (i ? pref[i - 1] : 0);
   }

   const ll inf = (ll)1e18;
   struct entry {
      ll cost = -inf;
      int x, y;
   };

   vector <entry> dp(m + 5);
   dp[0] = {0, 0, 0};

   for (int w = 0; w <= m; ++w) {
      if (dp[w].x < n1 // go to w + 1
             && dp[w + 1].cost < dp[w].cost + one[dp[w].x]) {
         dp[w + 1].cost = dp[w].cost + one[dp[w].x];
         dp[w + 1].x = dp[w].x + 1;
         dp[w + 1].y = dp[w].y;
      }
      if (dp[w].y < n2 // go to w + 2
            && dp[w + 2].cost < dp[w].cost + two[dp[w].y]) {
         dp[w + 2].cost = dp[w].cost + two[dp[w].y];
         dp[w + 2].x = dp[w].x;
         dp[w + 2].y = dp[w].y + 1;
      }
   }

   for (int w = 1; w <= m; ++w) {
      dp[w].cost = max(dp[w - 1].cost, dp[w].cost);
   }

   ll mx = dp[m].cost;
   for (int i = 0; i < n3; ++i) { // use (i + 1) 3's
      if (m - 3 * (i + 1) >= 0) {
         mx = max(dp[m - 3*(i + 1)].cost + pref[i], mx);
      }
      else break;
   }

   cout << mx << '\n';

   return EXIT_SUCCESS;
}

