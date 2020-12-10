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
#define PREC      cout.precision (5); cout << fixed
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

void preproc() {
}

struct Seg {
  double x1, y1, x2, y2, d;
};

int n;
const int N = 15;
Seg sg[N];
double one[N][1 << N];
double two[N][1 << N];

void solve() {
  for (int i = 0; i < n; ++i) {
    cin >> sg[i].x1 >> sg[i].y1 >> sg[i].x2 >> sg[i].y2;
    sg[i].d = hypot(sg[i].x1 - sg[i].x2, sg[i].y1 - sg[i].y2);
  }

  for (int i = 0; i < n; ++i) {
    for (int mask = 0; mask < (1 << n); ++mask)
      one[i][mask] = two[i][mask] = 1e18;
    one[i][1 << i] = two[i][1 << i] = sg[i].d;
  }

  for (int mask = 1; mask < (1 << n); ++mask) {
    for (int i = 0; i < n; ++i) {
      if (mask & (1 << i)) {
        double &olddp_one = one[i][mask];
        double &olddp_two = two[i][mask];
        for (int j = 0; j < n; ++j) {
          // i and j to join
          if (!(mask & (1 << j))) { // i is present and j isn't, so update j in the mask
            double &nwdp_one = one[j][mask ^ (1 << j)];
            double &nwdp_two = two[j][mask ^ (1 << j)];

            nwdp_one = min({nwdp_one,
                olddp_one + hypot(sg[i].x2 - sg[j].x1, sg[i].y2 - sg[j].y1) + sg[j].d,
                olddp_two + hypot(sg[i].x1 - sg[j].x1, sg[i].y1 - sg[j].y1) + sg[j].d
                });
            nwdp_two = min({nwdp_two,
                olddp_one + hypot(sg[i].x2 - sg[j].x2, sg[i].y2 - sg[j].y2) + sg[j].d,
                olddp_two + hypot(sg[i].x1 - sg[j].x2, sg[i].y1 - sg[j].y2) + sg[j].d
                });

          }
        }
      }
    }
  }

  double res = 1e18;
  for (int i = 0; i < n; ++i)
    res = min({res, one[i][(1 << n) - 1], two[i][(1 << n) - 1]});
  cout << res << '\n';
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  // cin >> tc;
  for (int Tt = 1; cin >> n, n; ++Tt) {
    cout << "Case " << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
