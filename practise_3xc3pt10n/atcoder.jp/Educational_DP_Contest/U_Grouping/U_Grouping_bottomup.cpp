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

const ll inf = (ll)1e18;
const int N = 17;
int n;
int a[N][N];
ll dp[1 << N];
ll wgt[1 << N];
// dp[mask] := max weight that can be achieved if we have grouped 'mask' in optimal way
// wgt[mask] := weight of that mask

void solve() {
   //preprocessing in O(2^n * n^2)
   for (int mask = 0; mask < (1 << n); ++mask) {
      wgt[mask] = 0;
      for (int i = 0; i < n; ++i)
         for (int j = i + 1; j < n; ++j)
            if ((mask & (1 << i)) && (mask & (1 << j)))
               wgt[mask] += a[i][j];
   }

   // O(3^n)
   dp[0] = 0;
   for (int mask = 1; mask < (1 << n); ++mask) {
      for (int sub_mask = mask; sub_mask > 0; sub_mask = (sub_mask - 1) & mask) { // how to get subset of a mask
         dp[mask] = max(dp[mask], dp[mask - sub_mask] + wgt[sub_mask]);
      }
   }
   cout << dp[(1 << n) - 1] << '\n';
}

signed main() {
   IOS; PREC;
   cin >> n;
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         cin >> a[i][j];
   solve();
   return EXIT_SUCCESS;
}

