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
   function <void(int, int)> rec;
   const int N = 103;
   int mat[N][N];
   int n, k;

   rec = [&] (int idx, int kk) -> void { // idx row, and idx column
      if (kk == 0 || idx == n) {
         return;
      }
      mat[idx][idx] = 1;
      kk -= 1;
      int give = min(kk/2, n - 1 - idx + 1 - 1);
      for (int i = idx + 1; i <= idx + give; ++i) {
         mat[i][idx] = 1;
      }
      for (int j = idx + 1; j <= idx + give; ++j) {
         mat[idx][j] = 1;
      }
      kk -= 2 * give;
      rec(idx + 1, kk);
   };

   cin >> n >> k;
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         mat[i][j] = 0;

   if (n * n < k) cout << -1 << '\n';
   else {
      rec(0, k);
      for (int i = 0; i < n; ++i) {
         for (int j = 0; j < n; ++j) {
            cout << mat[i][j] << ' ';
         }
         cout << '\n';
      }
   }
   return EXIT_SUCCESS;
}
