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

const int N = (int)3e5 + 10;
string s;
int n;
int ones_pref[N], zeroes_suff[N];

signed main() {
   IOS; PREC;
   cin >> n >> s;
   //W as 1 and E as 0
   for (int i = 0; i < n; ++i) {
      if (i == 0) {
         ones_pref[i] = (s[i] == 'W');
      }
      else {
         ones_pref[i] = ones_pref[i - 1] + (s[i] == 'W');
      }
   }

   for (int i = n - 1; i >= 0; --i) {
      if (i == n - 1) {
         zeroes_suff[i] = (s[i] == 'E');
      }
      else {
         zeroes_suff[i] = zeroes_suff[i + 1] + (s[i] == 'E');
      }
   }

   int mn = INT_MAX;
   for (int i = 0; i < n; ++i) {
      if (i == 0) {
         mn = min(mn, zeroes_suff[i + 1]);
      }
      else if (i == n - 1) {
         mn = min(mn, ones_pref[i - 1]);
      }
      else mn = min(mn, zeroes_suff[i + 1] + ones_pref[i - 1]);
   }
   cout << mn << '\n';

   return EXIT_SUCCESS;
}
