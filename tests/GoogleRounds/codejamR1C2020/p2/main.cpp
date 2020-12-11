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

template <class T = long long> T giveRand (const T& low, const T& high) {
   auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
   mt19937 mt_rand(seed);
   return uniform_int_distribution<T> (low, high)(mt_rand); //closed interval [low, high]
}

void solve() {
  int D = 26, U;
  cin >> U;

  int maxq = (int)1e4;
  vector <pair <string, string>> qr(maxq);
  vector <vector<pair <int, int>>> pos;
  map <char, int> mp;
  vector <char> dmp(10);

  for (int q = 0, idx = 0; q < maxq; ++q) {
    cin >> qr[q].first >> qr[q].second;
    // debug(qr[q]);
    for (char ch : qr[q].second)
      if (mp.find(ch) == mp.end()) {
        mp[ch] = idx, dmp[idx] = ch;
        ++idx;
      }
  }

  int alsize = (int)mp.size();
  pos.assign(alsize, vector<pair <int, int>> (10));
  assert(alsize == 10);

  for (int i = 0; i < alsize; ++i)
    for (int d = 0; d < 10; ++d)
      pos[i][d] = make_pair(0, d);

  for (int q = 0; q < maxq; ++q) {
    int rsz = (int)qr[q].second.size();
    assert(rsz != 0);
    long long maxqll = 1;
    int tmp = rsz; while(tmp--) maxqll *= 10;
    maxqll -= 1;

    if (qr[q].first != "-1") {
      long long qrll = 0;
      for (char hhh : qr[q].first)
        qrll = qrll * 10 + (hhh - '0');
      maxqll = min(maxqll, qrll);
    }

    long long qll = giveRand(1ll, maxqll);

    // long long qll = 1e9;
    string sqll = "", rs = qr[q].second;
    while (qll) {
      sqll += char((qll % 10) + '0');
      qll /= 10;
    }

    reverse(sqll.begin(), sqll.end());
    debug(qr[q].first, sqll);
    for (int i = 0; i < rsz; ++i) {
      int midx = mp[qr[q].second[i]];
      int digit = (int)sqll[i] - '0';
      assert(midx >= 0 && midx < 10 && digit >= 0 && digit < 10);
      ++pos[midx][digit].first;
    }
  }

  sort(pos.begin(), pos.end(), greater <vector <pair<int, int>>> ());

  vector <char> res(10, 'x');
  for (int i = 0; i < 10; ++i) {
    for (int dd = 0; dd < 10; ++dd) {
      int d = pos[i][dd].second;
      if (res[d] == 'x') {
        res[d] = dmp[i];
        break;
      }
    }
  }

  for (int i = 0; i < 10; ++i)
    cout << res[i];
  cout << '\n';
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

