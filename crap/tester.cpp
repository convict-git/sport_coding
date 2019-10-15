#include      <bits/stdc++.h>
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
// #pragma GCC   optimize ("Ofast")
// #pragma GCC   optimize ("unroll-loops")
// #pragma GCC   target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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

string s;
void solve_bs() {
   int n = (int)s.size();
   set <char> st;
   for (char ch : s) st.insert(ch);
   int mx_cnt = (int)st.size(); // this is the answer for max distinct char

   auto iterate = [&] (int len)->bool {
      int cnt[26] = {0};
      int cur_cnt = 0, mx = 0;
      for (int i = 0; i < len; ++i) {
         ++cnt[s[i] - 'a'];
         if (cnt[s[i] - 'a'] == 1) ++cur_cnt;
      }
      mx = cur_cnt;

      for (int i = 1; i + len - 1 <= n - 1; ++i) {
         if (cnt[s[i - 1] - 'a'] == 1) { // does i - 1 contribute in cur_cnt
            --cur_cnt;
         }
         --cnt[s[i - 1] - 'a'];

         if (cnt[s[i + len - 1] - 'a'] == 0) { // i + len - 1 contribute in cur_cnt
            ++cur_cnt;
         }
         ++cnt[s[i + len - 1] - 'a'];
         mx = max(mx, cur_cnt);
      }
      if (mx == mx_cnt) return true;
      else return false;
   };

   int ans = 0;
   for (int l = 1, h = n; l <= h; ans = l) { // binary search the answer
      int g = (l + h)/2;
      if (iterate(g)) h = g - 1;
      else l = g + 1;
   }
   cout << ans << '\n';
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      cin >> s;
      solve_bs();
   }
   return EXIT_SUCCESS;
}
