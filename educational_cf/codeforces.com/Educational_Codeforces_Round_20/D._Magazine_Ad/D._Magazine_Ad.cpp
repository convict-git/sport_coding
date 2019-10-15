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
   int k, n;
   string s;
   vector <int> next_dash;
   cin >> k;
   cin.ignore();
   getline(cin, s);
   n = (int)s.size();
   next_dash.assign(n, - 1);

   for (char &ch : s) {
      if (ch == ' ') ch = '-';
   }

   int cur = n - 1;
   for (int i = n - 1; i >= 0; --i) {
      next_dash[i] = cur;
      if (s[i] == '-') {
         cur = i;
      }
   }

   function <bool(int)> iterate;
   iterate = [&] (int len) -> bool {
      int line = 0;
      for (int start = 0; start < n; ) {
         int end = next_dash[start];
         while (end < n &&
               next_dash[end] - start + 1 <= len &&
               end != next_dash[end]) {
            end = next_dash[end];
         }
         if (end - start + 1 > len) {
            return false;
         }
//          for (int i = start ; i <= end; ++i)
//          cerr << s[i]; cerr << '\n'; // this prints answer
         start = end + 1;
         ++line;
         if (line > k) {
            return false;
         }
      }
      return true;
   };

   int ans;
   for (int l = 0, h = (int)1e6 + 10; l <= h ; ans = l) { // binary search the answer
      int len = (l + h)/2;
      if (iterate(len)) {
         h = len - 1;
      }
      else {
         l = len + 1;
      }
   }
   cout << ans << '\n';

   return EXIT_SUCCESS;
}
