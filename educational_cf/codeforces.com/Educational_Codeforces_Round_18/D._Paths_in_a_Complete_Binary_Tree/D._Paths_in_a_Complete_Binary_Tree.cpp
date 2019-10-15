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

ll n, n_root;
int q;
string s;

void solve() {
   stack <ll> st;
   int mx_depth = (log2(n + 1));
   ll low = 1, high = n;
   ll mid = (low + high)/2;
   int depth = 1;
   st.push(mid);

   while (mid != n_root) {
      if (n_root < mid) {
         high = mid - 1;
      }
      else low = mid + 1;
      mid = (low + high)/2;
      depth += 1;
      st.push(mid);
   }

   for (char ch : s) {
      if ((depth == mx_depth && (ch == 'L' || ch == 'R'))
            || (depth == 1 && ch == 'U')) {
         continue;
      }

      if (ch == 'L') {
         high = mid - 1;
         mid = (low + high)/2;
         depth += 1;
         st.push(mid);
      }
      else if (ch == 'R') {
         low = mid + 1;
         mid = (low + high)/2;
         depth += 1;
         st.push(mid);
      }

      if (ch == 'U') {
         ll t = st.top();
         st.pop();
         mid = st.top();
         depth -= 1;
         if (t < mid) high = low + 2*(high - low + 1);
         else low = high - 2*(high - low + 1);
      }
   }
   cout << mid << '\n';
}

signed main() {
   IOS; PREC;
   cin >> n >> q;
   while (q--) {
      cin >> n_root >> s;
      solve();
   }

   return EXIT_SUCCESS;
}
