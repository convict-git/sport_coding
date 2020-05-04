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
template <typename F, typename T = int>
class sparse_table {
  public:
    static const int D = 21;
    int n;
    vector <vector <T>> dp, who;
    vector <int> LOG;

    sparse_table (const vector <T> &v) {
      n = (int)v.size();
      dp.assign(D + 1, vector <T> (n));
      who.assign(D + 1, vector <T> (n));
      LOG.assign(n + 1, 0);

      for (int i = 0; i < n; ++i)
        dp[0][i] = v[i];
      iota(who[0].begin(), who[0].end(), 0);

      for (int k = 1; k <= D; ++k)
        for (int i = 0; i < n; ++i)
          if (i + T(k) - 1 < n) {
            T lt = dp[k - 1][i], rt = dp[k - 1][i + T(k - 1)];
            if (F()(lt, rt) == lt) { // max
              who[k][i] = who[k - 1][i];
              dp[k][i] = lt;
            }
            else {
              who[k][i] = who[k - 1][i + T(k - 1)];
              dp[k][i] = rt;
            }
          }

      for (int i = 2; i <= n; ++i)
        LOG[i] = LOG[i / 2] + 1;
    }

    pair <T, int> get (int l, int r) {
      int k = LOG[r - l + 1];
      T lt = dp[k][l], rt = dp[k][r - T(k) + 1];
      return (F ()(lt, rt) == lt ? make_pair(who[k][l], lt) : make_pair(who[k][r - T(k) + 1], rt)); // max
    }

    pair <int, int> get_range (int x) {
      int L = x, R = x;
      for (int k = D; k >= 0; --k)
        if (R + T(k) - 1 < n && dp[k][R] >= dp[0][x])
          R += T(k);
      --R;
      for (int k = D; k >= 0; --k)
        if (L - T(k) + 1 >= 0 && dp[k][L - T(k) + 1] >= dp[0][x])
          L -= T(k);
      ++L;
      return make_pair(L, R);
    }
};

template <typename T>
class binop {
  public:
    T operator () (const T &x, const T &y) {
      return max(x, y);
    }
};
#undef T

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

  vector <int> df(n);
  for (int i = 0; i < n; ++i)
    df[i] = ar[i].first - (i + 1 < n ? ar[i + 1].first : 0);

  sparse_table <binop <int>, int> ST(df);

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
        pair <int, int> gt = ST.get(leftk, rightk);
        int k = gt.first;
        int fx = df[i], sx = df[j], rx = df[k];
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
