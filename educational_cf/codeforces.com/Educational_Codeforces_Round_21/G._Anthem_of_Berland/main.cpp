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

vector <int> pref_func (string &s) { // O(|s|)
  int n = (int)s.size();
  vector <int> pi(n);
   pi[0] = 0;
   int sz = (int)s.size();
   for (int i = 1; i < sz; ++i) {
      int len_j = pi[i-1];
      int j = len_j - 1;
      while (len_j > 0 && s[j + 1] != s[i]) {
         len_j = pi[j];
         j = len_j - 1;
      }
      if (s[len_j] == s[i])
         ++len_j;
      pi[i] = len_j;
   }
   return pi;
}

// each state represents prefix length
// transition : length * char -> length
vector <vector <int>> calc_fsm(string t) { // O(|s| * 26)
  int n = (int)t.size();
  t += '#';
  vector <vector <int>> fsm(n + 1, vector <int> (26));
  vector <int> pi = pref_func(t);
  for (int len = 0; len <= n; ++len) {
    for (int ch = 0; ch < 26; ++ch) {
      if (len == 0 || t[len] == char('a' + ch))
        fsm[len][ch] = len + (t[len] == char('a' + ch));
      else
        fsm[len][ch] = fsm[pi[len - 1]][ch];
    }
  }
  return fsm;
}

signed main() {
  IOS; PREC;
  string s, t;
  cin >> s >> t;
  vector<vector<int>> fsm = calc_fsm(t);

  int n = (int)s.size(), m = (int)t.size();
  int dp[m + 1][2];
  for (int i = 0; i <= m; ++i)
    for (int j = 0; j < 2; ++j)
      dp[i][j] = -1;

  dp[0][0] = 0;

  int nxt;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j <= m; ++j) if (dp[j][i & 1] != -1) {
      if (s[i] == '?') {
        for (int ch = 0; ch < 26; ++ch) {
          nxt = fsm[j][ch];
          dp[nxt][!(i & 1)] = max(dp[nxt][!(i & 1)], dp[j][i & 1] + (nxt == m));
        }
      }
      else {
        nxt = fsm[j][s[i] - 'a'];
        dp[nxt][!(i & 1)] = max(dp[nxt][!(i & 1)], dp[j][i & 1] + (nxt == m));
      }
    }
  }

  int res = 0;
  for (int i = 0; i <= m; ++i) res = max(res, dp[i][n & 1]);
  cout << res << '\n';

  return EXIT_SUCCESS;
}
