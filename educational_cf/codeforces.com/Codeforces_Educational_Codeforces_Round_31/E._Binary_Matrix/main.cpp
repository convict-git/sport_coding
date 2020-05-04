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
//
const int M = (1 << 14) + 10;
int pp[M], pn[M], pi[M + M], mark[M], vis[M + M], rnk[M + M];
int prv[M], nxt[M];
char foo[M];

inline int node (int x) {
    int y = x, tmp;
    while (y != pi[y]) y = pi[y];
    while (x != pi[x]) tmp = pi[x], pi[x] = y, x = tmp;
    return y;
};

void solve() {
  int n, m;
  scanf("%i%i", &n, &m);
  // cin >> n >> m;

  for (int i = 0; i < 2 * m; ++i) pi[i] = i, rnk[i] = 1;

  int res = 0;
  for (int i = 0; i < m; ++i) prv[i] = 0;
  for (int rot = 0; rot <= n; ++rot) {
    for (int i = 0; i < m; ++i) nxt[i] = 0;
    if (rot != n) {
      scanf("%s", foo);
      for (int i = 0; i < m/4; ++i) {
        char ch = foo[i];
        int el = (ch - '0' >= 0 && ch - '0' <= 9 ? 0 + (ch - '0') : 10 + (ch - 'A'));
        for (int j = 0; j < 4; ++j)
          if (el & (1 << j)) nxt[i * 4 + 3 - j] = 1;
      }
    }

    // set right local pointers
    for (int i = 0; i < m; ++i) pn[i] = -1;
    for (int i = m - 1, rt = m - 1; i >= 0; --i)
      if (nxt[i]) pn[i] = rt;
      else rt = i - 1;

    // first : normalize the dsu for the previous string

    for (int i = 0; i < m; ++i) mark[i] = -1;
    for (int i = 0; i < m; ++i)  {
      if (prv[i]) {
        int lt = pp[i] + m;
        int nd = node(lt);
        i = pp[i];
        if (nd >= m) continue;
        if (mark[nd] == -1)
          mark[nd] = lt;
        pi[lt] = mark[nd];
      }
    }
    for (int i = 0; i < m; ++i) pi[i] = i;
    for (int i = 0; i < m; ++i)
      if (prv[i])
        pi[i] = pi[i + m] - m;
    for (int i = m; i < m + m; ++i) pi[i] = i;

    // second : merge components

    for (int i = 0; i < m; ++i) {
      if (nxt[i] && prv[i]) {
        int lt = node(pn[i] + m);
        int nd = node(pp[i]);
        // merge(lt, nd);
        pi[lt] = nd;
      }
    }

    // third : update the answer based on left out components (They will never be seen again)

    for (int i = 0; i < m + m; ++i) vis[i] = 0;

    for (int i = m; i < m + m; ++i) {
      if (nxt[i - m]) {
        int v = node(pn[i - m] + m);
        vis[v] = true;
      }
    }
    for (int i = 0; i < m; ++i) {
      if (prv[i]) {
        int v = node(pp[i]);
        if (!vis[v])
          ++res, vis[v] = true;
      }
    }
    // update and reset
    for (int i = 0; i < m; ++i)
      pp[i] = pn[i], prv[i] = nxt[i];
  }
  printf("%i\n", res);
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

