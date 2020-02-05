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

const int Mod = 1e9 + 7;
inline int add (int x, int y) { return (x+y) % Mod; }
inline int sub (int x, int y) { return (x-y+Mod) % Mod; }
inline int mul (int x, int y) { return static_cast <int> (1ll*x*y % Mod); }
inline int pow (int x, int y) {
  int res=1;
  while (y) { if (y&1) res=mul(res, x); x=mul(x, x), y>>=1; }
  return res;
}
inline int dv (int x, int y) { return mul(x, pow(y, Mod-2)); }

const int MAX_P = 2101000;
vector <int> primes = {2}, powers;
void sieve() {
   vector <bool> isPrime(MAX_P + 1, true);
   for (int i = 3; i*2 <= MAX_P; i += 2) {
      int p = 0;
      while (1ll * i*(i + p) <= MAX_P) isPrime[i*(i + p)] = false, ++p;
   }
   for (int i = 3; i <= MAX_P; i += 2) {
      if (isPrime[i]) primes.push_back(i);
   }
}

int total_divisors(int n) {
   int td = 1; // total divisors of n
   int n_ref = n;
   for (int p : primes) {
      if (1ll*p*p > 1ll*n_ref) break;
      int alpha = 0;
      while (n%p == 0) n/=p, ++alpha;
      td *= (1 + alpha);
      powers.push_back(alpha);
   }
   td *= (1 + (n != 1));
   return td;
}

const int N = (int)1e5 + 10;
const int LOG = 26;
int n;
int ar[N], val[N], mx[N][26], logn[N];
ll fq[N];
vector <pair <int, int>> gval;

inline int get_max(int l, int r) { // O(1)
  int j = logn[r - l + 1];
  return max(mx[l][j], mx[r - (1 << j) + 1][j]);
}

signed main() {
  IOS; PREC;
  logn[1] = 0;
  for (int i = 2; i < N; ++i) logn[i] = logn[i/2] + 1;

  sieve();
  for (int i = 0; i < N; ++i) {
    int td = total_divisors(i);
    val[i] = pow(i, (td % 2 == 1 ? (td - 1)/2 : td/2));
    if (td % 2 == 1) val[i] = mul(val[i], sqrt(i));
  }

  int tc;
  cin >> tc;
  while (tc--) {
    gval.clear();
    int q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) cin >> ar[i], mx[i][0] = ar[i];

    for (int d = 1; d < LOG; ++d) {
      for (int i = 0; i < n; ++i) {
        mx[i][d] = max(mx[i][d - 1], mx[i + (1 << (d - 1))][d - 1]);
      }
    }

    for (int i = 0; i < n; ++i) {
      int l = i + 1, h = n - 1;
      while (l <= h) {
        int g = (l + h) / 2;
        if (get_max(i, g) == ar[i]) l = g + 1;
        else h = g - 1;
      }
      int occ = (h - (i + 1) + 1);
      gval.push_back(make_pair(val[ar[i]], occ));
    }
    sort (gval.begin(), gval.end(), greater <pii> ());

    for (int i = 0; i < n; ++i) {
      fq[i] = 1ll * gval[i].second;
      if (i) fq[i] += fq[i - 1];
    }
    ///// l                               h
    //       i i+1 i+2 .......j j + 1          n-1
    // 2 2 2 5 3   4   3 5    2 7
    // l                      r
    // occ a[i] in final array is (j - (i+1) + 1)

    while (q--) {
      int idx;
      cin >> idx;
      int l = 0, h = n - 1;
      while (l <= h) {
        int g = (l + h) / 2;

      }
    }
  }
  return EXIT_SUCCESS;
}


