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

//seed_seq seq{
//   (uint64_t) chrono::duration_cast<chrono::nanoseconds>
//      (chrono::high_resolution_clock::now().time_since_epoch()).count(),
//      (uint64_t) __builtin_ia32_rdtsc(),
//      (uint64_t) (uintptr_t) make_unique<char>().get()
//};
// mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]

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

const int N = (int)1e5 + 10;
int n;
string s;
int pi[N];

void pref_func(const string &st) {
   pi[0] = 0;
   for (int i = 1; i < n; ++i) {
      int j_len = pi[i - 1];
      int j = j_len - 1;

      while (j_len > 0 && st[j + 1] != st[i]) {
         j_len = pi[j];
         j = j_len - 1;
      }
      if (st[j + 1] == st[i])
         ++j_len;
      pi[i] = j_len;
   }
}

void solve() {
   pref_func(s);
   int best_len = 0;
   for (int i = n - 1; i >= 0; --i) {
      int len = i + 1;
      int k = len - pi[len - 1];
      if (len % k == 0 && len / k == 2) {
         best_len = k;
         break;
      }
   }
   int offset = n - 2 * best_len;
   for (int i = 0; i < 8; ++i) {
      cout << s[(offset + i) % best_len];
   }
   cout << "...\n";
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      cin >> s;
      n = (int)s.size();
      solve();
   }

   return EXIT_SUCCESS;
}
