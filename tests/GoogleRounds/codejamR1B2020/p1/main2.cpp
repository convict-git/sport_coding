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

void solve() {
  int x, y;
  cin >> x >> y;
  for (int D = 0; D <= 10; ++D) {
    for (int mask = 0; mask < (1 << D); ++mask) {
      vector <int> tk, ot;
      for (int i = 0; i < D; ++i) {
        if (mask & (1 << i)) tk.push_back(i);
        else ot.push_back(i);
      }
      int lt = __builtin_popcount(mask);
      int rt = D - lt;
      // trying to make x
      int xgot = -1;
      for (int xsub = 0; xsub < (1 << lt); ++xsub) {
        int _x = x;
        for (int i = 0; i < lt; ++i) {
          if (xsub & (1 << i)) _x -= 1 << tk[i];
          else _x += 1 << tk[i];
        }
        if (_x == 0) {
          xgot = xsub;
          break;
        }
      }
      if (xgot != -1) {
        for (int ysub = 0; ysub < (1 << rt); ++ysub) {
          int _y = y;
          for (int i = 0; i < rt; ++i) {
            if (ysub & (1 << i)) _y -= 1 << ot[i];
            else _y += 1 << ot[i];
          }
          if (_y == 0) { // got the answer // convert from here // south + // east +
            vector <int> s[4];
            string res(D, 'S');
            for (int i = 0; i < lt; ++i) {
              if (xgot & (1 << i)) {
                res[tk[i]] = 'E';
                s[0].push_back(tk[i]);
              }
              else {
                res[tk[i]] = 'W';
                s[1].push_back(tk[i]);
              }
            }
            for (int i = 0; i < rt; ++i) {
              if (ysub & (1 << i)) {
                res[ot[i]] = 'N';
                s[2].push_back(ot[i]);
              }
              else {
                res[ot[i]] = 'S';
                s[3].push_back(ot[i]);
              }
            }
            debug(x, y);
            char mp[] = {'E', 'W', 'N', 'S'};
            for (int j = 0; j < 4; ++j) {
              cerr << mp[j] << ": ";
              for (int i = 0; i < (int)s[j].size(); ++i) {
                cerr << s[j][i] << ' ';
              }
              cerr << '\n';
            }
            cout << res << '\n';
            return;
          }
        }
      }
    }
  }
  cout << "IMPOSSIBLE\n";
}

signed main() {
  IOS; PREC;
  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    cout << "Case #" << Tt << ": ";
    solve();
    cout << flush;
    cerr << flush;
  }
  return EXIT_SUCCESS;
}