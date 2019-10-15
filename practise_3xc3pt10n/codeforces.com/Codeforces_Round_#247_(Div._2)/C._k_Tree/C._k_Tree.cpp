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
const int N = 103, Mod = (int)1e9 + 7;
int dp[N][2];
int cum[N][2]; //cum of dp, cum[i][s] = dp[0][s] + ..... + dp[i][s]
int n, k, d;
// dp[w][taken_d] = total no, of paths to get weight w such bool taken_d
//if bool is true, upto this state atleast one edge of >=d is taken

int add (int a, int b) {
   return (a + b) % Mod;
}
int sub (int a, int b) {
   return (a - b + Mod) % Mod;
}

inline int cum_cal(int l, int h, bool mode) {
   return sub(cum[h][mode], (l > 0 ? cum[l - 1][mode] : 0));
}

signed main() {
   IOS; PREC;
   cin >> n >> k >> d;

   dp[0][0] = 1, dp[0][1] = 0;
   cum[0][0] = 1, cum[0][1] = 0;
   //base case
   for (int w = 1, l, h; w <= n; ++w) {//  O (N)
      for (bool taken_d : {false, true}) {
         dp[w][taken_d] = 0;

         if (taken_d) {
            // comes from true
            h = w - 1, l = w - min(w, k);
            dp[w][taken_d] = add(dp[w][taken_d], cum_cal(l, h, true));

            // comes from false
            if (d <= w) {
               h = w - d, l = w - min(k, w);
               dp[w][taken_d] = add(dp[w][taken_d], cum_cal(l, h, false));
            }
         }
         else {
            // comes from false
            h = w - 1, l = w - min(d - 1, w);
            dp[w][taken_d] = add(dp[w][taken_d], cum_cal(l, h, false));
         }


         //update cummulative of dp
         cum[w][true] = add(cum[w - 1][true], dp[w][true]);
         cum[w][false] = add(cum[w - 1][false], dp[w][false]);

      }
   }
   //recurrence

   cout << dp[n][true] << '\n';

   return EXIT_SUCCESS;
}
