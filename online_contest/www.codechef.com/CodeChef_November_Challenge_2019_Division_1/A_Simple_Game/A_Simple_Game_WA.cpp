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
#define x         first
#define y         second
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
using   vi  =     vector <int>;
using   vl  =     vector<ll>;
using   vvi =     vector <vi>;
using   vp  =     vector <pii>;
using   vvp =     vector <vp>;
typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
  int operator () (pii x) const { return x.x*31 + x.y; }
};
gp_hash_table <pii, int, chash> mp;

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
/*}}}*/
/*****************************************************************************/
//Don’t practice until you get it right. Practice until you can’t get it wrong

signed main() {
  IOS; PREC;

  const int N = (int)1e4 + 10;
  const ll inf = (ll)1e18;
  ll dp[N][11][11];
  int a[N][11];
  int c[N];

  int tc; cin >> tc;
  while (tc--) {
    int n;
    cin >> n;
    fr(i, 0, n-1) fr (j, 0, 10) fr (k, 0, 10) dp[i][j][k] = -inf;

    fr(r, 0, n-1) {
      cin >> c[r];
      fr (j, 0, c[r]-1) cin >> a[r][j];
    }

    vector <pair <ll, ll>> mxx(n);
    vector <bool> single(n, false);

    for (int r = 0; r < n; ++r) {
      for (int i = 0; i < c[r]; ++i)
        dp[r][i][i] = a[r][i];
      for (int i = 0; i < c[r] - 1; ++i)
        dp[r][i][i + 1] = max(a[r][i], a[r][i + 1]);

      for (int len = 3; len <= c[r]; ++len) {
        for (int i = 0; i + len - 1 <= c[r] - 1; ++i) {
          int j = i + len - 1;
          ll lft = min(dp[r][i + 2][j], dp[r][i + 1][j - 1]);
          ll rgt = min(dp[r][i][j - 2], dp[r][i + 1][j - 1]);
          dp[r][i][j] = max(lft + a[r][i], rgt + a[r][j]);
        }
      }
      if (c[r] == 1) {
        mxx[r] = make_pair(dp[r][0][0], 0);
        single[r] = true;
      }
      else {
        ll mx = max(dp[r][0][c[r] - 2], dp[r][1][c[r] - 1]);
        ll mn = min(dp[r][0][c[r] - 2], dp[r][1][c[r] - 1]);
        mxx[r] = make_pair(mx, mn);
      }
    }

    sort (mxx.begin(), mxx.end(), greater <pair <ll, ll>>());
    ll ans = 0;
    ll ans1 = 0, ans2 = 0;
    for (int r = 0; r < n; ++r) {
      if (r == 0) ans += mxx[r].x, ans1 += mxx[r].x;
      else {
        ans += single[r] ? mxx[r].x : mxx[r].y;
        ans2 += single[r] ? mxx[r].x : mxx[r].y;
      }
    }
    cerr << "First " << ans1 << " Second : " << ans2 << '\n';
    cout << ans << '\n';
  }
  return EXIT_SUCCESS;

  // shit code!!! READ PROBLEM CAREFULLY NEXT TIME!!!
}
