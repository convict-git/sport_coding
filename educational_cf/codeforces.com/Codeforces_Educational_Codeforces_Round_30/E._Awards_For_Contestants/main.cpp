#include      <bits/stdc++.h> /*{{{*/
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#ifdef CONVICTION
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
#define bcnt(x)   __builtin_popcount(x)
#define bcntll(x) __builtin_popcountll(x)
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

#ifdef CONVICTION
void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]" << endl;}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif
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
#define T(x) (1 << (x))
void solve() {
  int n;
  cin >> n;
  vector <pair <int, int>> ar(n);
  {
    for (int i = 0; i < n; ++i) {
      cin >> ar[i].first;
      ar[i].second = i;
    }
    sort(ar.begin(), ar.end(), greater <pair <int, int>> ());
  }

  int D = 13;
  vector <vector <int>> dp(n, vector <int> (D + 1));
  vector <vector <int>> whoK(D + 1, vector <int> (n));
  vector <int> LG(n + 1);
  {
    for (int i = 1; i < n; ++i)
      dp[i - 1][0] = ar[i - 1].first - ar[i].first;
    dp[n - 1][0] = ar[n - 1].first;
    iota(whoK[0].begin(), whoK[0].end(), 0);

    for (int i = 2; i < n + 1; ++i)
      LG[i] = LG[i / 2] + 1;

    for (int k = 1; k <= D; ++k)
      for (int i = 0; i < n; ++i)
        if (i + T(k) - 1 < n) {
          int lt = dp[i][k - 1], rt = dp[i + T(k - 1)][k - 1];
          dp[i][k] = max(lt, rt);
          whoK[k][i] = (lt > rt ? whoK[k - 1][i] : whoK[k - 1][i + T(k - 1)]);
        }
  }

  auto mx = [&] (int x, int y) -> pair <int, int> {
    int k = LG[y - x + 1];
    int K = (dp[x][k] > dp[y - T(k) + 1][k] ? whoK[k][x] : whoK[k][y - T(k) + 1]);
    int m = max(dp[x][k], dp[y - T(k) + 1][k]);
    return make_pair(m, K);
  };

  int FX = INT_MIN, SX = INT_MIN, RX = INT_MIN, ii = -1, jj = -1, kk = -1;
  vector <pair <int, int>> b(n);
  {
    for (int i = 0; i < n; ++i) {
      for (int j = i + 1; j < n; ++j) {
        int li = i + 1, lj = j - i;
        if (li > 2 * lj || lj > 2 * li)
          continue;
        // chose some k, lk = k - j, lk <= 2 * min(lj, li), 2 * lk >= max(li, lj)
        int leftk = j + max(1, (max(li, lj) + (max(li, lj) & 1)) / 2);
        int rightk = j + min(2 * min(li, lj), n - 1 - j);
        if (leftk > rightk) continue;
        /*
        for (int k = leftk; k <= rightk; ++k) {
          int fx = dp[i][0], sx = dp[j][0], rx = dp[k][0];
          if (FX < fx || (FX == fx && SX < sx) || (FX == fx && SX == sx && RX < rx))
            FX = fx, SX = sx, RX = rx, ii = i, jj = j, kk = k;
        }
        */
        pair <int, int> gt = mx(leftk, rightk);
        int k = gt.second;
        int fx = dp[i][0], sx = dp[j][0], rx = dp[k][0];
        if (FX < fx || (FX == fx && SX < sx) || (FX == fx && SX == sx && RX < rx))
        FX = fx, SX = sx, RX = rx, ii = i, jj = j, kk = k;
      }
    }
  }
//   debug(FX, SX, RX, ii, jj, kk);
  for (int i = 0; i < n; ++i) {
    b[i].first = ar[i].second;
    if (i <= ii) b[i].second = 1;
    else if (i <= jj) b[i].second = 2;
    else if (i <= kk) b[i].second = 3;
    else b[i].second = -1;
  }
  sort(b.begin(), b.end());
  for (int i = 0; i < n; ++i)
    cout << b[i].second << ' ';
  cout << '\n';
}


signed main() {
  IOS; PREC;
  int tc = 1;
  // cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
