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
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update >
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
   it->empty(); cerr << " (Line : " << __LINE__ << ")" << endl;
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
   cerr << fixed << setprecision(15)
      << " [ " <<  *it << " : " << a  << " ] "<< ' ';
   err(++it, args...);
}

/*****************************************************************************/

const int N = (int)8004;
string s;
int dp[N], pi[N];
int n;

int dig(int k) {
   int c = 0;
   while (k) ++c, k /= 10;
   return c;
}

void pref_func(const string &st) {
   int m = (int)st.size();
   pi[0] = 0;

   for (int i = 1; i < m; ++i) {
      int j_len = pi[i - 1];
      int j = j_len - 1;

      while (j_len > 0 && st[j + 1] != st[i]) {
         j_len = pi[j];
         j = j_len - 1;
      }
      if (st[j + 1] == st[i]) ++j_len;
      pi[i] = j_len;
   }
}

void solve() {
   n = (int)s.size();

   for (int i = 0; i < n; ++i) {
      string sub = s.substr(0, i + 1);
      reverse(sub.begin(), sub.end());
      pref_func(sub);
      dp[i] = 1 + i + 1;

      for (int j = 0; j <= i; ++j) {
         int len = i + 1 - j;
         int k = len - pi[len - 1];
         if (len % k == 0) {
            if (j == 0) dp[i] = min(dp[i], dig(len/k) + k);
            else dp[i] = min(dp[i], dp[j - 1] + dig(len/k) + k);
         }
         else {
            if (j == 0) dp[i] = min(dp[i], 1 + len);
            else dp[i] = min(dp[i], dp[j - 1] + 1 + len);
         }
      }
   }
   cout << dp[n - 1] << '\n';
}

signed main() {
   IOS; PREC;
   cin >> s;
   solve();
   return EXIT_SUCCESS;
}
