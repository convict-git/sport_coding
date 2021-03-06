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
const int N = (int)1e6 + 10;
const int Log = 20;

string s;
int n, m;
int p[Log + 1][N], c[Log + 1][N], dp[Log + 1][N], lgn[N], idx[Log + 1][N];

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

int lcp (int i, int j) {
  int res = 0;
  for (int k = Log; k >= 0; --k) {
    if (i + (1 << k) - 1 > n || j + (1 << k) - 1 > n) continue;
    if (c[k][i] == c[k][j])
      i += (1 << k), j += (1 << k), res += (1 << k);
  }
  return res;
}

void print() {
  for (int i = 0; i < n; ++i) {
    int ii = p[Log][i];
    cerr << s.substr(ii, n - ii) << '\n';
  }
  cerr << endl;
}

signed main() {
  IOS; PREC;

  while (cin >> m, m) {
    cin >> s;
    if (m == 1) {
      cout << (int)s.size() << ' ' << 0 << '\n';
      continue;
    }
    s += "$";
    n = (int)s.size();
    cyclic_sort();

#define T(x) (1 << (x))

    lgn[1] = 0;
    for (int i = 2; i <= n + 1; ++i)
      lgn[i] = lgn[i / 2] + 1;

    for (int i = 0; i < n; ++i)
      idx[0][i] = p[Log][i];

    for (int i = 0; i < n - 1; ++i) {
      int ii = p[Log][i], jj = p[Log][i + 1];
      dp[0][i] = lcp(ii, jj);
    }

    for (int k = 1; k < Log; ++k)
      for (int i = 0; i < n; ++i)
        if (i + T(k) - 1 < n) {
          dp[k][i] = min(dp[k - 1][i], dp[k - 1][i + T(k - 1)]);
          idx[k][i] = max(idx[k - 1][i], idx[k - 1][i + T(k - 1)]);
        }

    auto mxidx = [&] (int x, int y) {
      int k = lgn[y - x + 1];
      return max(idx[k][x], idx[k][y - T(k) + 1]);
    };

    int mxlen = 0, id = -1;
    for (int i = 0; i < n - 1; ++i) {
      if (dp[0][i] == 0) continue;
      int j = i, midx = -1;
      for (int k = Log; k >= 0; --k) {
        if (j + T(k) - 1 < n - 1 && dp[k][j] >= dp[0][i])
          j += T(k);
      }
      --j;
      int jj = i;
      for (int k = Log; k >= 0; --k) {
        if (jj - T(k) + 1 >= 0 && dp[k][jj - T(k) + 1] >= dp[0][i])
          jj -= T(k);
      }
      ++jj;
      int len = j - jj + 2;
      midx = mxidx(jj, j + 1);

      if (len >= m && mxlen <= dp[0][i]) {
        if (mxlen == dp[0][i]) id = max(midx, id);
        else mxlen = dp[0][i], id = midx;
      }
    }

    if (id == -1) cout << "none\n";
    else cout << mxlen << ' ' << id << '\n';
  }

  return EXIT_SUCCESS;
}
