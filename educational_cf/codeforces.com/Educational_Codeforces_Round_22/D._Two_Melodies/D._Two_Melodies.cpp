#include      <bits/stdc++.h> /*{{{*/
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#ifndef CONVICTION
#pragma GCC       optimize ("Ofast")
#pragma GCC       optimize ("unroll-loops")
#pragma GCC       target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#define x         first
#define y         second
#define fr(i,x,y) for (int i = (int)x; i <= (int)y; ++i)
#define rv(i,x,y) for (int i = (int)x; i >= (int)y; --i)
#define cnt(x)    __builtin_popcount(x)
#define cntll(x)  __builtin_popcountll(x)
#define bg(x)     " [ " << #x << " : " << (x) << " ] "
#define un(x)     sort(x.begin(), x.end()), \
                  x.erase(unique(x.begin(), x.end()), x.end())
using   ll  =     long long;
using   ull =     unsigned long long;
using   ff  =     long double;
using   pii =     pair<int,int>;
using   pil =     pair<int,ll>;
using   vi  =     vector <int>;
using   vl  =     vector<ll>;
using   vvi =     vector <vi>;
using   vp  =     vector <pii>;
using   vvp =     vector <vp>;
typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
   int operator () (pii x) const { return x.x*31 + x.y; }
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
//         __                                           __
//        (**)                                         (**)
//        IIII                                         IIII
//        ####                                         ####
//        HHHH     Madness comes, and madness goes     HHHH
//        HHHH    An insane place, with insane moves   HHHH
//        ####   Battles without, for battles within   ####
//     ___IIII___        Where evil lives,          ___IIII___
//  .-`_._"**"_._`-.      and evil rules         .-`_._"**"_._`-.
// |/``  .`\/`.  ``\|    Breaking them up,      |/``  .`\/`.  ``\|
// `     }    {     '  just breaking them in    `     }    {     '
//       ) () (  Quickest way out, quickest way wins  ) () (
//       ( :: )      Never disclose, never betray     ( :: )
//       | :: |   Cease to speak or cease to breath   | :: |
//       | )( |        And when you kill a man,       | )( |
//       | || |          you're a murderer            | || |
//       | || |             Kill many                 | || |
//       | || |        and you're a conqueror         | || |
//       | || |        Kill them all ... Ooh..        | || |
//       | || |           Oh you're a God!            | || |
//       ( () )                       -Megadeth       ( () )
//        \  /                                         \  /
//         \/                                           \/
/*}}}*/
/*****************************************************************************/
//Don’t practice until you get it right. Practice until you can’t get it wrong
//

const int N = (int)5e3 + 10, M = (int)1e5 + 10;
int n;
int ar[N], dp[N][N];
int dpmod[7], dpnum[M];

signed main() {
   IOS; PREC;

   memset(dp, 0, sizeof(dp));
   memset(dpmod, 0, sizeof(dpmod));
   memset(dpnum, 0, sizeof(dpnum));

   cin >> n;
   for (int i = 1; i <= n; ++i) {
     cin >> ar[i];
   }

   int mx = 0;
   for (int j = 0; j <= n; ++j) {
     for (int i = 1; i <= n; ++i) {
       dpmod[ar[i] % 7] = 0;
       dpnum[ar[i] - 1] = dpnum[ar[i] + 1] = 0;
     }
     for (int i = j + 1; i <= n; ++i) {
       /*
       for (int k = 0; k < i; ++k) {
         if (k == 0 || abs(ar[i] - ar[k]) ==  1 || ar[i] % 7 == ar[k] % 7) {
           if (k > j) dp[i][j] = max(dp[k][j] + 1, dp[i][j]);
           else dp[i][j] = max(dp[j][k] + 1, dp[i][j]);
         }
       }
       mx = max(mx, dp[i][j]);
       */

       // debug(i, j, dp[i][j], dpmod[ar[i]%7], dpnum[ar[i]-1], dpnum[ar[i]+1], dp[j][0]);
       dp[i][j] = max({dpmod[ar[i] % 7], dpnum[ar[i] - 1], dpnum[ar[i] + 1], dp[j][0]}) + 1;
       dpmod[ar[i] % 7] = max(dpmod[ar[i] % 7], dp[i][j]);
       dpnum[ar[i]] = max(dpnum[ar[i]], dp[i][j]);
       // cerr << "dp(" << i << ", " << j << ") = " << dp[i][j] << '\n';
       mx = max(mx, dp[i][j]);
     }
   }
   cout << mx << '\n';


   return EXIT_SUCCESS;
}

