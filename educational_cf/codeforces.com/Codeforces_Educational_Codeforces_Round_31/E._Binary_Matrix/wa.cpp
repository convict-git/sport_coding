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

map <char, string> mp = {
  {'0', "0000"},
  {'1', "0001"},
  {'2', "0010"},
  {'3', "0011"},
  {'4', "0100"},
  {'5', "0101"},
  {'6', "0110"},
  {'7', "0111"},
  {'8', "1000"},
  {'9', "1001"},
  {'A', "1010"},
  {'B', "1011"},
  {'C', "1100"},
  {'D', "1101"},
  {'E', "1110"},
  {'F', "1111"}
};


void solve() {
  int n, m, res = 0, X = 0;
  cin >> n >> m;
  string prv(m, '0'), nxt, s;
  vector <vector <int>> idx(m, vector <int> (2, -1));
  vector <vector <int>> last(m, vector <int> (2, -1));
  for (int i = 0; i <= n; ++i) {
    nxt.clear();
    if (i != n) {
      cin >> s;
      for (auto ch : s) nxt += mp[ch];
    }
    else nxt.assign(m, '0');
    for (int j = m - 1, pp = m - 1; j >= 0; --j) {
      if (prv[j] == '0') pp = j - 1;
      else last[j][!(i & 1)] = pp;
    }
    for (int j = m - 1, pp = m - 1; j >= 0; --j) {
      if (nxt[j] == '0') pp = j - 1;
      else last[j][i & 1] = pp;
    }
    for (int j = 0; j < m; ++j)
      idx[j][i & 1] = -1;

    for (int j = 0; j < m; ++j) {
      if (nxt[j] == '1') {
        if (last[j][i & 1] == j && prv[j] == '0' && idx[j][i & 1] == -1){
          idx[last[j][i & 1]][i & 1] = ++X;
        }
        else if (prv[j] == '1')  {
          if (idx[last[j][i & 1]][i & 1] == -1) {
            idx[last[j][i & 1]][i & 1] = idx[last[j][!(i & 1)]][!(i & 1)];
          }
          else {
            idx[last[j][!(i & 1)]][!(i & 1)] = idx[last[j][i & 1]][i & 1];
          }
        }
      }
    }
    set <int> aval, taken;
    for (int j = 0; j < m; ++j)
      if (nxt[j] == '1')
        aval.insert(idx[last[j][i & 1]][i & 1]), j = last[j][i & 1];

    debug(aval);
    for (int j = 0; j < m; ++j)
      if (prv[j] == '1') {
        int val = idx[last[j][!(i & 1)]][!(i & 1)];
        if (aval.find(val) == aval.end() && taken.find(val) == taken.end())
          ++res, taken.insert(val);
        j = last[j][!(i & 1)];
      }

    prv = nxt;
    debug(res);
  }
  cerr << st << '\n';
  cout << res << '\n';
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


