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
#define x first
#define y second
#define fr(i, x, y) for (int i = x; i <= y; ++i)
#define fR(i, x, y) for (int i = x; i >= y; --i)
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
using vvi = vector<vi>;
using vp = vector<pii>;
using vl = vector<ll>;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
    ordered_set;

struct chash
{
  int operator()(pii x) const { return x.x * 31 + x.y; }
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
/*}}}*/
/*****************************************************************************/
//Don’t practice until you get it right. Practice until you can’t get it wrong

/*
int pi[26];

inline int rep (int x) {
  return pi[x] = (x == pi[x] ? x : rep(pi[x]));
}

inline void merge (int x, int y) {
  x = rep(x), y = rep(y);
  pi[x] = y;
}
*/

int w[26][26];

signed main()
{
  IOS;
  PREC;
  //   fr(i, 0, 25) pi[i] = i;
  fr(i, 0, 25) fr(j, 0, 25) w[i][j] = 0;

  int n;
  cin >> n;
  vector<string> store(n);

  fr(i, 0, n - 1)
  {
    cin >> store[i];
    fr(j, 0, (int)store[i].size() - 1) fr(k, 0, (int)store[i].size() - 1)
        w[store[i][j] - 'a'][store[i][k] - 'a'] = 1, w[store[i][k] - 'a'][store[i][j] - 'a'] = 1;
    //     for (int j = 1; j < (int)store[i].size(); ++j)
    //       merge(store[i][0]-'a', store[i][j]-'a');
  }

  vi vis(26, false);
  function<void(int)> dfs = [&](int u) -> void {
    vis[u] = true;
    fr(i, 0, 25) if (w[u][i] && !vis[i]) dfs(i);
  };

  int cc_idx = 0;
  fr(i, 0, n - 1) if (!vis[store[i][0] - 'a']) dfs(store[i][0] - 'a'), ++cc_idx;

  cout << cc_idx << '\n';

  //   set <int> s;
  //   fr(i, 0, n-1) s.insert(rep(store[i][0]-'a'));
  //   cout << s.size() << '\n';

  return EXIT_SUCCESS;
}
