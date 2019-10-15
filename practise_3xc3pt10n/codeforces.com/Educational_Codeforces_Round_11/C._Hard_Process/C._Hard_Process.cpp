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

int n, k;
vector <int> ar;
vector <int> z_idx;

void solve() {
   int sz = (int)z_idx.size();

   int mx_len = 0, best_i = -1;
   if (sz == 2) mx_len = n;
   for (int i = 1; i <= sz - 2; ++i) {
      // l : idx of last zero (which is not considered)
      // r : idx of next zero (which is not considered)
      int l = (i - k + 1 >= 1 ? z_idx[i - k + 1 - 1] : z_idx[0]);
      int r = z_idx[i + 1];
      if (mx_len < r - l - 1) {
         mx_len = r - l - 1;
         best_i = i;
      }
   }
   cout << mx_len << '\n';
   for (int i = 1; i <= sz - 2; ++i) {
      if (i <= best_i && best_i - i + 1 <= k)
         ar[z_idx[i]] = 1;
   }
   for (int i = 1; i <= n; ++i)
      cout << ar[i] << " \n"[i == n];
}

signed main() {
   IOS; PREC;
   cin >> n >> k;

   ar.assign(n + 1, 0);
   z_idx.push_back(0);

   for (int i = 1; i <= n; ++i) {
      cin >> ar[i];
      if (!ar[i]) z_idx.push_back(i);
   }
   z_idx.push_back(n + 1);
   solve();

   return EXIT_SUCCESS;
}

