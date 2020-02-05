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

const int N = (int)1e6 + 10;
const int D = 20;
int mn[N][D], mx[N][D], LOG[N], a[N];

inline int get_max(int l, int r) {
  int j = LOG[r - l + 1];
  return max(mx[l][j], mx[r - (1 << j) + 1][j]);
}

inline int get_min(int l, int r) {
  int j = LOG[r - l + 1];
  return min(mn[l][j], mn[r - (1 << j) + 1][j]);
}

signed main()
{
  IOS; PREC;
  LOG[1] = 0;
  for (int i = 2; i < N; ++i)
    LOG[i] = LOG[i / 2] + 1;

  int n;
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
    mx[i][0] = mn[i][0] = a[i];
  }

  for (int j = 1; j < D; ++j){
    for (int i = 0; i < n; ++i) {
      mx[i][j] = max(mx[i][j - 1], mx[i + (1 << (j - 1))][j - 1]);
      mn[i][j] = min(mn[i][j - 1], mn[i + (1 << (j - 1))][j - 1]);
    }
  }

  ll res = 0;
  for (int i = 0; i < n; ++i) {
    int l = i, h = n - 1, mxl, mxr, mnl, mnr;
    while (l <= h) {
      int g = (l + h) / 2;
      int mxv = get_max(i, g);
      if (mxv == a[i])
        l = g + 1;
      else
        h = g - 1;
    } /// answer will be in h
    mxr = h;
    l = 0, h = i;
    while (l <= h)
    {
      int g = (l + h) / 2;
      int mxv = get_max(g, i);
      if (mxv == a[i])
        h = g - 1;
      else
        l = g + 1;
    } /// answer will be in l
    mxl = l;
    ll cur = 1ll * a[i] * (mxr - i + 1) * (i - mxl + 1);
    res += cur;
    // debug("MAX",a[i], mxl, i, mxr, mxr-i+1, i-mxl+1, cur);

    l = i, h = n - 1;
    while (l <= h)
    {
      int g = (l + h) / 2;
      int mnv = get_min(i, g);
      if (mnv == a[i])
        l = g + 1;
      else
        h = g - 1;
    } /// answer will be in h
    mnr = h;
    l = 0, h = i;
    while (l <= h)
    {
      int g = (l + h) / 2;
      int mnv = get_min(g, i);
      if (mnv == a[i])
        h = g - 1;
      else
        l = g + 1;
    } /// answer will be in l
    mnl = l;
    cur = 1ll * a[i] * (mnr - i + 1) * (i - mnl + 1);
    res -= cur;
    // debug("MIN",a[i], mnl, i, mnr, mnr-i+1, i-mnl+1, cur);
  }
  cout << res << '\n';
  return EXIT_SUCCESS;
}

