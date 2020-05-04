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

int A[4][4], B[4][4], vis[4][4];
ll k;
int a, b;

void updsc (pair <int, int> &c, int &x, int &y) {
  x += (c.first == 3 && c.second == 2)
    || (c.first == 2 && c.second == 1)
    || (c.first == 1 && c.second == 3);

  y += (c.second == 3 && c.first == 2)
    || (c.second == 2 && c.first == 1)
    || (c.second == 1 && c.first == 3);
}

signed main() {
  IOS; PREC;
  memset(vis, 0, sizeof(vis));
  cin >> k >> a >> b;

  for (int i = 1; i <= 3; ++i)
    for (int j = 1; j <= 3; ++j)
      cin >> A[i][j];

  for (int i = 1; i <= 3; ++i)
    for (int j = 1; j <= 3; ++j)
      cin >> B[i][j];

  vector <pair <int, int> > cc, stk;

  stk.push_back(make_pair(a, b));
  vis[a][b] = true;

  int x = A[a][b], y = B[a][b];
  while (!vis[x][y]) {
    int x_ = x, y_ = y;
    stk.push_back(make_pair(x, y));
    x = A[x_][y_], y = B[x_][y_];
    vis[x_][y_] = true;
  }

  while (!stk.empty()) {
    int curx = stk.back().first, cury = stk.back().second;
    cc.push_back(stk.back());
    stk.pop_back();

    if (curx == x && cury == y)
      break;
  }
  reverse(cc.begin(), cc.end());

  int alen = (int)stk.size(), clen = (int)cc.size();

  int la = 0, lb = 0;
  for (int i = 0; i < min(k, 1ll * alen); ++i)
    updsc(stk[i], la, lb);

  int ca = 0, cb = 0;
  for (int i = 0; i < clen; ++i)
    updsc(cc[i], ca, cb);

  k -= min(k, 1ll * alen);
  int rema = 0, remb = 0;
  if (k > 0) {
    for (int i = 0; i < k % clen; ++i)
      updsc(cc[i], rema, remb);
  }

  cout << 1ll * (k / clen) * ca + la + rema << ' ' << 1ll * (k / clen) * cb + lb + remb << '\n';

  return EXIT_SUCCESS;
}


