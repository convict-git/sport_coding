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

const int N = (int)1e6 + 10;
int seg[4 * N], ez[4 * N], fl[4 * N];
map <ll, int> mp;
ll demap[N];
vector <pair <int, pll>> queries;
vector <ll> qs{1};
int n, q, idx = 0;

void lzupd (int x, int l, int r) {
  if (ez[x]) {
    seg[x] = (ez[x] == 1 ? r - l + 1 : 0);
    if (l != r) {
      ez[x + x + 1] = ez[x + x + 2] = ez[x];
      fl[x + x + 1] = fl[x + x + 2] = 0;
    }
    ez[x] = 0;
  }
  if (fl[x]) {
    seg[x] = (r - l + 1) - seg[x];
    if (l != r) {
      fl[x + x + 1] ^= 1, fl[x + x + 2] ^= 1;
    }
    fl[x] = 0;
  }
}

void insert (int l, int r, int x, int ql, int qr, int v, int f) {
  lzupd(x, l, r);
  int mid = (l + r) / 2;
  if (ql > r || qr < l) return;
  if (l >= ql && r <= qr) {
    if (v != 0) {
      seg[x] = (v == 1 ? r - l + 1 : 0);
      if (l != r) {
        ez[x + x + 1] = ez[x + x + 2] = v;
        fl[x + x + 1] = fl[x + x + 2] = 0;
      }
    }
    else {
      seg[x] = (r - l + 1) - seg[x];
      if (l != r) {
        fl[x + x + 1] ^= 1, fl[x + x + 2] ^= 1;
      }
    }
    return;
  }
  insert (l, mid, x + x + 1, ql, qr, v, f);
  insert (mid + 1, r, x + x + 2, ql, qr, v, f);
  seg[x] = seg[x + x + 1] + seg[x + x + 2];
}

int bs (int x, int l, int r) {
  lzupd(x, l, r);
  // debug(x, l, r, seg[x]);
  if (seg[x] == r - l + 1) return -1;
  if (l == r) return l;
  int mid = (l + r)/2;
  int res = bs(x + x + 1, l, mid);

  if (res == -1) return bs(x + x + 2, mid + 1, r);
  else return res;
}

signed main() {
  IOS; PREC;
  mp.clear();
  memset(seg, 0, sizeof(seg));
  memset(ez, 0, sizeof(ez));
  memset(fl, 0, sizeof(fl));

  cin >> q;
  for (int i = 0; i < q; ++i) {
    int t; ll l, r;
    cin >> t >> l >> r;
    queries.push_back(make_pair(t, make_pair(l, r)));
    qs.push_back(l), qs.push_back(r);
    qs.push_back(l + 1), qs.push_back(r + 1);
  }
  un(qs);

  for (ll el : qs)  {
    if (mp.find(el) == mp.end()) {
      mp[el] = idx;
      demap[idx] = el;
      ++idx;
    }
  }

  n = idx;
  for (auto el : queries) {
    int l = (int) (lower_bound(qs.begin(), qs.end(), el.Y.X) - qs.begin());
    int r = (int) (lower_bound(qs.begin(), qs.end(), el.Y.Y) - qs.begin());

    if (el.X != 3) {
      el.X = (el.X == 1 ? 1 : -1);
      insert(0, n - 1, 0, l, r, el.X, 0);
    }
    else
      insert(0, n - 1, 0, l, r, 0, 1);

    int res = bs (0, 0, n - 1);
    cout << demap[res] << '\n';
    // show(0, 0, n-1); cerr << "\n";
  }

  return EXIT_SUCCESS;
}


