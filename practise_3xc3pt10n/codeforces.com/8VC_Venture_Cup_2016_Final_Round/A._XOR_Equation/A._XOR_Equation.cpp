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

const int N = 44;
ll s, x;
ll ar[N][2];
// arr[i][0] = contribution in whole sum of ith bit from a and b if mask had 0 at ith position
// arr[i][1] = contribution in whole sum of ith bit from a and b if mask had 1 at ith position

void solve() {
   ll x_ref = x;
   for (int i = 0; i < N; ++i) {
      if (x_ref & 1LL) { // 0 and 1 or 1 and 0
         ar[i][0] = (1LL << i) + 0;
         ar[i][1] = 0 + (1LL << i);
      }
      else {
         ar[i][0] = 0 + 0;
         ar[i][1] = (1LL << i) + (1LL << i);
      }
      x_ref >>= 1LL;
   }

   vector <ll> val1, val2;
   //first 22 bits
   for (int mask = 0; mask < (1 << N/2); ++mask) {
      ll val = 0;
      for (int j = 0; j < N/2; ++j) {
         if (mask & (1 << j)) val += ar[j][1];
         else val += ar[j][0];
      }
      val1.push_back(val);
   }
   //last 22 bits
   for (int mask = 0; mask < (1 << N/2); ++mask) {
      ll val = 0;
      for (int j = 0; j < N/2; ++j) {
         if (mask & (1 << j)) val += ar[N/2 + j][1];
         else val += ar[N/2 + j][0];
      }
      val2.push_back(val);
   }

   sort(val1.begin(), val1.end());
   sort(val2.begin(), val2.end());

   ll ans = 0;
   int sz = 1 << (N/2);
   for (int i = 0, l, h; i < sz; ++i) {
      ll val = s - val1[i];
      if (val < 0) continue;
      l = 0, h = sz - 1;
      while (l <= h) {
         int g = (l + h)/2;
         if (val2[g] <= val) l = g + 1;
         else h = g - 1;
      }
      int lst = h; // last index that works

      l = 0, h = sz - 1;
      while (l <= h) {
         int g = (l + h)/2;
         if (val2[g] < val) l = g + 1;
         else h = g - 1;
      }
      int frst = l; //first index that works

      if (lst == -1) continue;
      ans += (lst - frst + 1);
   }
   if (s == x) ans -= 2;
   cout << ans << '\n';
}

signed main() {
   IOS; PREC;
   cin >> s >> x;
   solve();

   return EXIT_SUCCESS;
}
