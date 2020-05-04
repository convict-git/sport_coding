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

struct suffix_array {
  static const int N = (int)1e5 + 10;
  static const int Log = 18;

  string s;
  int p[Log + 1][N], c[Log + 1][N]; // p : permutation, c : equivalence class, sa : suffix array
  int lp[N], sa[N];
  int n;

/// #warning for N = 1e6, N * logN * logN is approx 4e8 (so it may timeout)
  void cyclic_sort () { // O(|s| * (log|s|)^2)
    iota(p[0], p[0] + n, 0);
    sort (p[0], p[0] + n, [&] (const int &x, const int &y) -> bool {
        return s[x] < s[y];
        });

    int ck = 0;
    c[0][p[0][0]] = ck;
    for (int i = 1; i < n; ++i)
      c[0][p[0][i]] = ck += (s[p[0][i]] != s[p[0][i - 1]]);

    for (int k = 1; k <= Log; ++k) {
      int pw = 1 << (k - 1);
      iota(p[k], p[k] + n, 0);

      sort (p[k], p[k] + n, [&] (const int &x, const int &y) -> bool {
          return c[k - 1][x] < c[k - 1][y] ||
          (c[k - 1][x] == c[k - 1][y] &&
           c[k - 1][(x + pw) % n] < c[k - 1][(y + pw) % n]);
          });

      c[k][p[k][0]] = ck = 0;
      for (int i = 1; i < n; ++i)
        c[k][p[k][i]] =
          ck += (c[k - 1][p[k][i]] != c[k - 1][p[k][i - 1]]
              || c[k - 1][(p[k][i] + pw) % n] != c[k - 1][(p[k][i - 1] + pw) % n]);
    }
  }

  int lcp(int i, int j) { // in cyclic string (NOTE, otherwise change starting value of k)
    int res = 0;
    for (int k = Log; k >= 0; --k) {
      if (i + (1 << k) - 1 > n || j + (1 << k) - 1 > n) continue; // to remove the cyclic constraint
      if (c[k][i] == c[k][j])
        i += (1 << k), j += (1 << k), res += (1 << k);
    }
    return res;
  }

  suffix_array (string s_) {
    s = s_ + "$";
    n = (int)s.size();
    cyclic_sort();
// #warning p[Log][i] corresponding to the string "$", and n is len of (original string + "$")
    for (int i = 0; i < n; ++i) {
      sa[i] = p[Log][i];
      if (i != n - 1) lp[i] = lcp(p[Log][i], p[Log][i + 1]);
    }
    // print();
  }

  int compare (int i, int j, int k, int len) { // O(1)
    pair <int, int> s1 = make_pair(c[k][i], c[k][(i + len - (1 << k)) % n]);
    pair <int, int> s2 = make_pair(c[k][j], c[k][(j + len - (1 << k)) % n]);
    return s1 == s2 ? 0 : s1 < s2 ? -1 : 1;
  }

  void print() {
    for (int i = 0; i < n; ++i)
      cerr << s.substr(sa[i], n - sa[i]) << '\n';
    cerr << '\n';
  }
};

const int Mod = (int)1e9 + 7;
inline int add (int x, int y) { return (1ll * x + y + (Mod << 1)) % Mod; }
inline int sub (int x, int y) { return (1ll * x - y + (Mod << 1)) % Mod; }
inline int mul (int x, int y) { return (int) (1ll*(x + Mod) * (y + Mod) % Mod); }
inline int pow (int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) res = mul(res, x);
    x = mul(x, x), y >>= 1;
  }
  return res;
}
inline int inv (int x) { return pow(x, Mod - 2); }
inline int dv (int x, int y) { return mul(x, inv(y)); }

signed main() {
  IOS; PREC;

  int tc;
  cin >> tc;
  for (int T = 1; T <= tc; ++T) {
    cout << "Case #" << T << ": ";
    string s;
    int k;
    cin >> s >> k;
    suffix_array S(s);

#define c2(x) dv(mul(x, x - 1), 2)

    int res = 0, cur = 0;
    bool last = false;
    for (int i = 0; i < S.n; ++i) {
      int len = S.n - S.sa[i] - 1;
      if ((i == S.n - 1 || S.lp[i] < k) && last) {
        assert(len >= k);
        cur = add(cur, len - k + 1);
        res = add(res, c2(cur));
        cur = last = 0;
      }
      else if (S.lp[i] >= k) {
        cur = add(cur, len - k + 1);
        last = true;
      }
      else if (len >= k) {
        res = add(res, c2(len - k + 1));
      }
    }
    cout << res << '\n';
  }

  return EXIT_SUCCESS;
}


