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

const int N = (int)1e6 + 10;
int seg[4 * N];
void update (int l, int r, int x, int q) {
   if (q > r || q < l) return;
   if (l == r) {
      seg[x] += 1;
      return;
   }
   int mid = (l + r)/2;
   update (l, mid, x + x + 1, q);
   update (mid + 1, r, x + x + 2, q);
   seg[x] = seg[x + x + 1] + seg[x + x + 2];
}

int get (int l, int r, int x, int ql, int qr) {
   if (l > qr || r < ql) return 0;
   if (l >= ql && r <= qr) {
      return seg[x];
   }
   int mid = (l + r)/2;
   int lget = get (l, mid, x + x + 1, ql, qr);
   int rget = get (mid + 1, r, x + x + 2, ql, qr);
   return lget + rget;
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      int n;
      cin >> n;
      vector <int> ar(n);
      int mx_wgt = 0;
      for (int i = 0; i < n; ++i) {
         cin >> ar[i];
         mx_wgt = max(ar[i], mx_wgt);
      }
      fill (seg, seg + 4 * mx_wgt, 0);
      reverse(ar.begin(), ar.end());

      vector <int> ans(n);
      update(0, mx_wgt, 0, ar[0]);
      for (int i = 1; i < n; ++i) {
         ans[i] = get(0, mx_wgt, 0, 0, ar[i] - 1);
         update(0, mx_wgt, 0, ar[i]);
      }
      reverse (ans.begin(), ans.end());
      for (int i = 0; i < n; ++i)
         cout << ans[i] << " \n" [i == n - 1];
   }
   return EXIT_SUCCESS;
}
