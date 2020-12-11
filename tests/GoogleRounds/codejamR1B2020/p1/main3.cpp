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
      string res(D, '#');
      vector <int> tk, ot;
      int smlt = 0, smrt = 0;
      for (int i = 0; i < D; ++i) {
        if (mask & (1 << i)) tk.push_back(i), smlt += (1 << i);
        else ot.push_back(i), smrt += (1 << i);
      }
      int lt = __builtin_popcount(mask);
      int rt = D - lt;

      int _x = x, _y = y;
      if (abs(smlt) == _x) {
        for (int i = 0; i < lt; ++i)
          res[tk[i]] = (_x >= 0 ? 'E' : 'W');
        _x = 0;
      }
      if (_x) {
        for (int i = 0; i < lt; ++i) {
          if (smlt - (1 << (tk[i] + 1)) == _x) {
            _x = 0;
            for (int j = 0; j < lt; ++j) {
              if (i == j) res[tk[j]] = 'W';
              else res[tk[j]] = 'E';
            }
            break;
          }
          else if ((1 << (tk[i] + 1)) - smlt == _x) {
            _x = 0;
            for (int j = 0; j < lt; ++j) {
              if (i == j) res[tk[j]] = 'E';
              else res[tk[j]] = 'W';
            }
            break;
          }
        }
      }

      if (_x == 0) {
        if (abs(smrt) == _y) {
          for (int i = 0; i < rt; ++i)
            res[ot[i]] = (_y >= 0 ? 'S' : 'N');
          _y = 0;
        }
        if (_y) {
          for (int i = 0; i < rt; ++i) {
            if (smrt - (1 << (ot[i] + 1)) == _y) {
              _y = 0;
              for (int j = 0; j < rt; ++j) {
                if (i == j) res[ot[j]] = 'S';
                else res[ot[j]] = 'N';
              }
              break;
            }
            else if ((1 << (ot[i] + 1)) - smrt == _y) {
              _y = 0;
              for (int j = 0; j < rt; ++j) {
                if (i == j) res[ot[j]] = 'N';
                else res[ot[j]] = 'S';
              }
              break;
            }
          }
        }
        if (_y == 0) {
          cout << res << '\n';
          return;
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
  }
  return EXIT_SUCCESS;
}
