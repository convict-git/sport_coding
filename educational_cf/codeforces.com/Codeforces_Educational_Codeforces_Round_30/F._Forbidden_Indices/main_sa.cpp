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
void _print() {cerr << "]\n";}
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
template <typename __S = int>
class binop {
  public:
    __S operator () (const __S &x, const __S &y) {
      return min(x, y);
    }
};

template <class __F = long long, class __B = binop <__F>>
class sparse_table {
  public:
    static const int D = 21;
    int n;
    vector <vector <__F>> dp, who;
    vector <int> LOG;

    sparse_table (const vector <__F> &v) {
      n = static_cast <int> (v.size());
      dp.assign(D + 1, vector <__F> (n));
      who.assign(D + 1, vector <__F> (n));
      LOG.assign(n + 1, 0);

      for (int i = 0; i < n; ++i)
        dp[0][i] = v[i];
      iota(who[0].begin(), who[0].end(), 0);

      for (int k = 1; k <= D; ++k)
        for (int i = 0; i < n; ++i)
          if (i + T(k) - 1 < n) {
            __F lt = dp[k - 1][i], rt = dp[k - 1][i + T(k - 1)];
            if (__B() (lt, rt) == lt) { // max or min
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

    pair <__F, int> get (int l, int r) {
      int k = LOG[r - l + 1];
      __F lt = dp[k][l], rt = dp[k][r - T(k) + 1];
      return (__B () (lt, rt) == lt ? make_pair(who[k][l], lt) : make_pair(who[k][r - T(k) + 1], rt)); // max or min
    }

    pair <int, int> get_range (int idx) {
      int L = idx, R = idx;
      for (int k = D; k >= 0; --k)
        if (R + T(k) - 1 < n && dp[k][R] >= dp[0][idx])
          R += T(k);
      --R;
      for (int k = D; k >= 0; --k)
        if (L - T(k) + 1 >= 0 && dp[k][L - T(k) + 1] >= dp[0][idx])
          L -= T(k);
      ++L;
      return make_pair(L, R);
    }
};
#undef T

struct suffix_array {
  const int Log = 20;

  string s;
  vector <vector <int>> p, c;
  vector <int> lp, sa;
  int n;

  void cyclic_sort () { // O(|s| * (log|s|)^2)
    iota(p[0].begin(), p[0].end(), 0);
    sort (p[0].begin(), p[0].end(), [&] (const int &x, const int &y) -> bool {
        return s[x] < s[y];
        });

    int ck = 0;
    c[0][p[0][0]] = ck;
    for (int i = 1; i < n; ++i)
      c[0][p[0][i]] = ck += (s[p[0][i]] != s[p[0][i - 1]]);

    for (int k = 1; k <= Log; ++k) {
      int pw = 1 << (k - 1);
      iota(p[k].begin(), p[k].end(), 0);

      sort (p[k].begin(), p[k].end(), [&] (const int &x, const int &y) -> bool {
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
    p.assign(Log + 1, vector <int> (n));
    c.assign(Log + 1, vector <int> (n));
    sa.assign(n + 1, 0);
    lp.assign(n + 1, 0);

    cyclic_sort();
    for (int i = 0; i < n; ++i) {
      sa[i] = p[Log][i];
      if (i != n - 1) lp[i] = lcp(p[Log][i], p[Log][i + 1]);
    }
  }

  int compare (int i, int j, int k, int len) { // O(1)
    pair <int, int> s1 = make_pair(c[k][i], c[k][(i + len - (1 << k)) % n]);
    pair <int, int> s2 = make_pair(c[k][j], c[k][(j + len - (1 << k)) % n]);
    return s1 == s2 ? 0 : s1 < s2 ? -1 : 1;
  }

  friend ostream& operator << (ostream &os, const suffix_array &S) {
    for (int i = 0; i < S.n; ++i) {
      os << S.s.substr(i, S.n - i) << '\n';
    }
    return os;
  }
};

#define T(x) (1 << (x))
void solve() {
  int n;
  string s, idx;
  cin >> n >> s >> idx;
  reverse(s.begin(), s.end());
  reverse(idx.begin(), idx.end());
  suffix_array S(s);

  vector <int> use, lcp;
  for (int i = 0; i < n; ++i) {
    if (idx[i] == '0') use.push_back(i);
  }
  if (use.size() == 0) {
    cout << 0 << '\n';
    return;
  }
  sort(use.begin(), use.end(), [&] (int p, int q) -> bool {
      return S.c[S.Log][p] < S.c[S.Log][q];
      });

  int sz = (int)use.size();
  lcp.assign(sz - 1, 0);
  for (int i = 0; i < sz - 1; ++i) {
    lcp[i] = S.lcp(use[i], use[i + 1]); } // debug(use, lcp);

  sparse_table <int, binop<int>> ST(lcp);
  long long mx = 0;
  {
    for (int i = 0; i < sz - 1; ++i) {
      if (lcp[i] == 0) continue;
      pair <int, int> rg = ST.get_range(i);
      int L = rg.first, R = rg.second;
      mx = max(mx, 1ll * (R - L + 2) * lcp[i]);
    }
    for (int i = 0; i < sz; ++i)
      mx = max(mx, 1ll * n - use[i]);
  }
  cout << mx << '\n';
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


