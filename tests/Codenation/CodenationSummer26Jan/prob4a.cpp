// Hack it and have it ;) //
/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows!* * * * * * */
#include <bits/stdc++.h> /*{{{*/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#ifndef CONVICTION
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

#define IOS                         \
  ios_base::sync_with_stdio(false); \
  cin.tie(nullptr)
#define PREC          \
  cout.precision(10); \
  cout << fixed
#define X first
#define Y second
#define sz(x) (int)x.size()
#define fr(i, x, y) for (int i = (int)x; i <= (int)y; ++i)
#define rv(i, x, y) for (int i = (int)x; i >= (int)y; --i)
#define cnt(x) __builtin_popcount(x)
#define cntll(x) __builtin_popcountll(x)
#define bg(x) " [ " << #x << " : " << (x) << " ] "
#define un(x) sort(x.begin(), x.end()), \
              x.erase(unique(x.begin(), x.end()), x.end())
using ll = long long;
using ull = unsigned long long;
using ff = long double;
using pii = pair<int, int>;
using pil = pair<int, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using vvl = vector<vl>;
using vp = vector<pii>;
using vvp = vector<vp>;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
    ordered_set;

struct chash
{
  int operator()(pii x) const { return x.X * 31 + x.Y; }
};
gp_hash_table<pii, int, chash> mp;

#if __cplusplus > 201103L
seed_seq seq{
    (uint64_t)chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count(),
    (uint64_t)__builtin_ia32_rdtsc(),
    (uint64_t)(uintptr_t)make_unique<char>().get()};
mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]
#else
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rng(seed);
#endif

#define debug(args...)                                                         \
  {                                                                            \
    /* WARNING : do NOT compile this debug func calls with following flags: // \
     * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/     \
    string _s = #args;                                                         \
    replace(_s.begin(), _s.end(), ',', ' ');                                   \
    stringstream _ss(_s);                                                      \
    istream_iterator<string> _it(_ss);                                         \
    err(_it, args);                                                            \
  }
void err(istream_iterator<string> it)
{
  it->empty();
  cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args)
{
  cerr << fixed << setprecision(15)
       << " [ " << *it << " : " << a << " ] " << ' ';
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

int n;
const int N = 21;
vector<vector<int>> T;
vector<int> vis;
ll dp[N][N]; // number of subgraphs with diameter j with root at i as dp[i][j]

void root_at(int u, int pr) {
  vis[u] = true;
  for (auto vit = T[u].begin(); vit != T[u].end(); ++vit) {
    if ((*vit) == pr) {
      T[u].erase(vit);
      break;
    }
  }
  for (int v : T[u]) {
    if (!vis[v])
      root_at(v, u);
  }
}

void dfs(int u) {
  vis[u] = true;
  for (int v : T[u])
    if (!vis[u])
      dfs(v);
  for (int j = 1; j < n; ++j) dp[u][j] = 0;
  dp[u][0] = 1;

  if (sz(T[u]) >= 2) {
    for (int j = 2; j <= n - 1; ++j) { // diameter
      for (int x = 0; x <= j - 2; ++x) {
        int y = (j - 2) - x;
        for (int ii = 0; ii < sz(T[u]); ++ii) {
          for (int jj = ii + 1; jj < sz(T[u]); ++j) {
            dp[u][j] += dp[T[u][ii]][x] * dp[T[u][jj]][y];
          }
        }
      }
    }
  }
  if (sz(T[u]) >= 1) {
    for (int j = 1; j <= n - 1; ++j) { // diameter
      for (int ii = 0; ii < sz(T[u]); ++ii) {
        dp[u][j] += dp[T[u][ii]][j - 1];
      }
    }
  }
}

signed main() {
  IOS; PREC;
  cin >> n;
  T.assign(n, vector<int>());
  memset(dp, 0, sizeof(dp));

  for (int i = 0; i < n - 1; ++i) {
    int u, v;
    cin >> u >> v;
    --u, --v;
    T[u].push_back(v);
    T[v].push_back(u);
  }

  vis.assign(n, false);
  root_at(0, -1);

  // for (int i = 0; i < n; ++i) debug(i, sz(T[i]));

  vis.assign(n, false);
  dfs(0);

  for (int j = 1; j <= n - 1; ++j) {
    ll cur = 0;
    for (int i = 0; i < n; ++i)
      cur += dp[i][j];
    cout << cur << '\n';
  }

  return EXIT_SUCCESS;
}
