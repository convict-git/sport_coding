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

using ull = unsigned long long;
using Hash = pair <int, ull>;

class polyhash {
  public:
    static const int Mod = (int)1e9 + 123;
    static vector <int> pow_int;
    static vector <ull> pow_ull;
    static int p; // take p such that a[i] < p < Mod, gcd(p, Mod) = 1

    static int gen_base (const int l, const int r) {
      int base = uniform_int_distribution<int>(l + 1, r - 1) (rng);
      return base % 2 == 0 ? base - 1 : base;
    }
    static void calc_pow(int mx_len) {
      while ((int)pow_int.size() <= mx_len + 1) { // calc powers
        pow_int.push_back(int(1ll * pow_int.back() * p % Mod));
        pow_ull.push_back(pow_ull.back() * p);
      }
    }
    int sz;
    vector <int> s;
    vector <int> pref_int;
    vector <ull> pref_ull;

    void encode(const string &st) {
      s.assign(sz, 0);
      for (int i = 0; i < sz; ++i) s[i] = st[i];
    }

    polyhash (const string &st) {
      sz = (int)st.size();
      encode(st);
      pref_int.assign(sz + 1u, 0);
      pref_ull.assign(sz + 1u, 0);
      assert(p < Mod);

      calc_pow(sz + 1);

      for (int i = 0; i < sz; ++i) {
        assert(p > s[i]);
        pref_int[i] = int(1ll*s[i]*pow_int[i] % Mod);
        pref_int[i] = (pref_int[i] + (i > 0 ? pref_int[i - 1] : 0)) % Mod;
        pref_ull[i] = s[i]*pow_ull[i] + (i > 0 ? pref_ull[i - 1] : 0);
      }
    }

    inline Hash operator()
      (const int pos, const int len, const int mx_len = -1) const {
        assert(pos + len <= sz);
        int hash_int = pref_int[pos + len - 1];
        ull hash_ull = pref_ull[pos + len - 1];
        if (pos != 0) {
          hash_int = (hash_int - pref_int[pos - 1] + Mod) % Mod;
          hash_ull = hash_ull - pref_ull[pos - 1];
        }
        if (mx_len != -1) { // for direct comparison between prefixes
          //else multiply with opposite powers
          assert (mx_len < (int)pow_int.size());
          hash_int = int(1ll*hash_int*pow_int[mx_len - (pos+len-1)] % Mod);
          hash_ull *= pow_ull[mx_len - (pos+len-1)];
        }
        return make_pair(hash_int, hash_ull);
      }
    //indexing from 0, len >= 1

    bool compare (int i, int len1, int j, int len2, int mx_len) {
      assert(i + len1 <= sz && j + len2 <= sz);
      int len = min(len1, len2);
      int l = 1, h = len;
      while (l <= h) {
        int glen = (l + h)/2;
        if ((*this)(i, glen, mx_len) == (*this)(j, glen, mx_len))
          l = glen + 1;
        else h = glen - 1;
      }
      //l is length of first point of difference
      return ((l > len && len1 < len2) || (s[i + l - 1] < s[j + l - 1]));
    }

    Hash inf_ext (int i, int len, int o_len, int mx_len) {
      function <ull(ull, int)> gp_ull;
      function <int(int, int)> gp_int;
      gp_ull = [&](ull a, int k) -> ull {
        ull a_sq = a * a;
        if (k == 1) return 1;
        else if (k & 1) return 1 + a * gp_ull(a, k - 1);
        else return (1 + a) * gp_ull (a_sq, k/2);
      };
      gp_int = [&] (int a, int k)->int {
        int a_sq = int(1ll * a * a % Mod);
        if (k == 1) return 1;
        else if(k & 1) return int((1 + (1ll * a * gp_int(a, k - 1)%Mod)));
        else return int(1ll * (1 + a) * gp_int (a_sq, k/2) % Mod);
      };

      Hash h = (*this)(i, len, mx_len);
      int hx = int(1ll * h.first * pow_int[len] % Mod);
      ull hy = h.second * pow_ull[len] * gp_ull(p, o_len);
      hx = int(1ll * hx * gp_int(p, o_len) % Mod);
      return make_pair(hx, hy);
    }

#define T(x) (1 << (x))
    int lcp (int i, int j, int mx_len) {
      int ii = i, jj = j;
      for (int k = 18; k >= 0; --k) {
        if (ii + T(k) - 1 < sz && jj + T(k) - 1 < sz) {
          if ((*this)(ii, T(k), mx_len) == (*this)(jj, T(k), mx_len))
            ii += T(k), jj += T(k);
        }
      }
      --ii, --jj;
      return (ii - i + 1);
    }
};

int polyhash::p = polyhash::gen_base(256, polyhash::Mod);
vector <int> polyhash::pow_int{1};
vector <ull> polyhash::pow_ull{1};
// int polyhash::p = 31; // 31 for [a ... z], 53 for [a..z, A..Z]


#define T(x) (1 << (x))
void solve() {
  const int D = 18;
  int n;
  string s, idx;
  cin >> n >> s >> idx;
  reverse(s.begin(), s.end());
  reverse(idx.begin(), idx.end());
  polyhash S(s);

  int sz = 0;
  vector <int> use, lcp;
  {
    for (int i = 0; i < n; ++i) {
      if (idx[i] == '0') use.push_back(i);
    }
    if (use.size() == 0) {
      cout << 0 << '\n';
      return;
    }
    sort(use.begin(), use.end(), [&] (int p, int q) -> bool {
        return S.compare(p, n - p, q, n - q, n);
        });

    sz = (int)use.size();
    lcp.assign(sz - 1, 0);
    for (int i = 0; i < sz - 1; ++i) {
      lcp[i] = S.lcp(use[i], use[i + 1], n);
    }
  }

  vector <vector <int>> dp(sz - 1, vector <int> (D + 1));
  {
    for (int i = 0; i < sz - 1; ++i)
      dp[i][0] = lcp[i];
    for (int k = 1; k <= D; ++k) {
      for (int i = 0; i < sz - 1; ++i) {
        if (i + T(k) - 1 < sz - 1)
          dp[i][k] = min(dp[i][k - 1], dp[i + T(k - 1)][k - 1]);
      }
    }
  }

  long long mx = 0;
  {
    for (int i = 0; i < sz - 1; ++i) {
      int h = dp[i][0];
      int L = i, R = i;
      for (int k = D; k >= 0; --k) {
        if (R + T(k) - 1 < sz - 1 && dp[R][k] >= h)
          R += T(k);
      }
      --R;
      for (int k = D; k >= 0; --k) {
        if (L - T(k) + 1 >= 0 && dp[L - T(k) + 1][k] >= h)
          L -= T(k);
      }
      ++L;
      mx = max(mx, 1ll * (R - L + 2) * h);
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

