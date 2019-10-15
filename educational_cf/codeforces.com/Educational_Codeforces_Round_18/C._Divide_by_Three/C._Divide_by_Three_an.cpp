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

const int N = (int)1e5 + 10, infi = (int)1e9;
int dp[N][2][3]; // max length
string s;
int n;
bool take = true;

void solve() {
   n = (int)s.size();
   for (int sum = 0; sum < 3; ++sum) {
      dp[0][!take][sum] = (sum == 0 ? 0 : -infi);
      dp[0][take][sum] = (sum == (s[0] - '0') % 3 ? 1 : -infi);
   }

   for (int i = 1; i < n; ++i) {
      for (int sum = 0; sum < 3; ++sum) {
         int from = (sum - (s[i] - '0') + 9) % 3;
         dp[i][take][sum] = max(dp[i - 1][take][from], dp[i - 1][!take][from]) + 1;
         dp[i][!take][sum] = max(dp[i - 1][!take][sum], dp[i - 1][take][sum]);

         if (s[i] - '0' == 0 && dp[i][take][sum] == 1) {
            // This is what you can miss and mess up
            dp[i][take][sum] = -infi;
         }
      }
   }

   int exist = max(dp[n - 1][take][0], dp[n - 1][!take][0]);
   if (!exist) {
      for (char ch : s) {
         if (ch == '0') {
            cout << 0 << '\n';
            return;
         }
      }
      cout << -1 << '\n';
   }
   else {
      vector <int> digit;
      int cur_sum = 0;
      int i = n - 1;
      while (i >= 0) {
         if (dp[i][take][cur_sum] > dp[i][!take][cur_sum]) {
            digit.push_back(s[i] - '0');
            cur_sum = (cur_sum - (s[i] - '0') + 9) % 3;
         }
         i -= 1;
      }
      reverse(digit.begin(), digit.end());
      for (int el : digit) cout << el;
      cout << '\n';
   }
}

signed main() {
   IOS; PREC;
   cin >> s;
   solve();
   return EXIT_SUCCESS;
}
