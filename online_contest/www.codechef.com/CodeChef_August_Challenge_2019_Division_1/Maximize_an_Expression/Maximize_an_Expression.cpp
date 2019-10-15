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

const int N = (int)1e5 + 5;
ff k[N], c[N], x_val[N], f_max;
int n;

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      cin >> n;
      for (int i = 0; i < n; ++i)
         cin >> k[i];
      for( int i = 0; i < n; ++i)
         cin >> c[i];

      ff frac = 0, num = 0, den = 0;
      bool ok = true;
      f_max = 0;

      for (int i = 0; i < n; ++i) {
         num += c[i] * k[i];
         den += (1 / k[i]);
      }

      frac = num / den;

      for (int i = 0; i < n; ++i) {
         x_val[i] =  frac / (k[i]*k[i]) - c[i];
         f_max += sqrt(x_val[i] + c[i]);
         if (x_val[i] + c[i] < 0) {
            ok = false;
            break;
         }
      }
      if (ok) {
         cout << f_max << ' ';
         for (int i = 0; i < n; ++i) {
            cout << x_val[i] << ' ';
         }
         cout << "\n";
      }
      else cout << -1 << '\n';
   }

   return EXIT_SUCCESS;
}
