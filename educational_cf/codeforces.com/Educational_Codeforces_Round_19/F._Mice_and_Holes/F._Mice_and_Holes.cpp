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
#define X         first
#define Y         second
#define sz(x)     (int)x.size()
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
using   pll =     pair<ll,ll>;
using   vi  =     vector <int>;
using   vl  =     vector<ll>;
using   vvi =     vector <vi>;
using   vvl =     vector <vl>;
using   vp  =     vector <pii>;
using   vvp =     vector <vp>;
typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
  int operator () (pii x) const { return x.X*31 + x.Y; }
};
gp_hash_table <pii, int, chash> gmp;

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

// dp(i, j) = 1...j mices in 1...i holes
// dp (i, j) = min {k < j} [dp(i - 1, k) + cost(k + 1, j, i)]
// also optimal k is monotonous to j for fixed i
// i.e. let A(i, j) be the optimal k, then A(i, j) <= A(i, j + 1)
// we can apply Divide & Conquer Optimization techinique to make this O(n^2 * m) into O(m*n*logn)

/*
 * Brute force solution - That works

for (int i = 1; i <= m; ++i) {
  for (int j = 1; j <= n; ++j) {
    dp[i][j] = inf;
    for (int k = 0; k <= j; ++k) {
      if (j - (k + 1) + 1 <= holes[i].second && dp[i - 1][k] < inf)
        dp[i][j] = min(dp[i][j], dp[i - 1][k] + cost(k + 1, j, i));
    }
  }
}
*/

const int N = 5010, M = 5010;
const long long inf = 1ll * 1e18;

int n, m;
int mices[N], prefcap[M];
pair <int, int> holes[M];
long long dp[2][N], prefsum[N];

long long cost (int l, int r, int j) {
  if (r < l) return 0;
  return prefsum[r] - prefsum[l - 1];
}

void dNc (int i, int l, int r, int kl, int kr) {
  if (r < l) return;
  int j = (l + r) / 2;
  int opt = j;

  for (int k = max(kl, j - holes[i].second); k <= min(j, kr); ++k) {
    if (dp[!(i & 1)][k] < inf &&
        dp[i & 1][j] > dp[!(i & 1)][k] + cost(k + 1, j, i))
    {
      dp[i & 1][j] = dp[!(i & 1)][k] + cost(k + 1, j, i);
      opt = k;
    }
  }

  dNc(i, l, j - 1, kl, opt);
  dNc(i, j + 1, r, opt, kr);
}

signed main()
{
  IOS; PREC;
  memset(prefsum, 0, sizeof(prefsum));
  memset(prefcap, 0, sizeof(prefcap));

  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    cin >> mices[i];
  }
  for (int i = 1; i <= m; ++i) {
    cin >> holes[i].first >> holes[i].second;
    prefcap[i] = prefcap[i - 1] + holes[i].second;
  }
  sort(mices + 1, mices + n + 1);
  sort(holes + 1, holes + m + 1);

  for (int i = 0; i <= n; ++i)
    dp[0][i] = dp[1][i] = inf;

  dp[0][0] = 0, dp[1][0] = 0;

  for (int i = 1; i <= m; ++i)  {
    for (int j = 1; j <= n; ++j) {
      prefsum[j] = 1ll * abs(mices[j] - holes[i].first) + prefsum[j - 1];
    }
    dNc(i, 1, n, 0, n);
  }

  if (dp[m & 1][n] >= inf) dp[m & 1][n] = -1;
  cout << dp[m & 1][n] << '\n';

  return EXIT_SUCCESS;
}
