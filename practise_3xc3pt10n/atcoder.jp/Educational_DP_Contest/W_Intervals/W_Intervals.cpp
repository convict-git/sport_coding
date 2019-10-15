#include      <bits/stdc++.h>
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#pragma GCC   optimize ("Ofast")
#pragma GCC   optimize ("unroll-loops")
#pragma GCC   target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS   ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC  cout.precision (10); cout << fixed
#define bg(x) " [ " << #x << " : " << (x) << " ] "
#define x     first
#define y     second
using   ll  = long long;
using   ff  = long double;
using   pii = pair<int,int>;
using   pil = pair<int,ll>;

typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
   int operator()(pii x) const { return x.x*31 + x.y; }
};
gp_hash_table <pii, int, chash> mp;

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

struct seg_max
{
   seg_max (int n, int Ar[] = nullptr) {
      sz = n;
      if (Ar == nullptr)
         memset(ar, 0, sizeof(ar));
      else for (int i = 0; i < sz; ar[i] = Ar[i], ++i);
      create(0, n - 1, 0);
   }

   static const int MXN = (int)2e5 + 10;
   static const ll inf = (ll)1e18;
   int sz;
   int ar[MXN];
   ll seg[4 * MXN], lz[4 * MXN];

   void create (int l, int r, int x) {
      lz[x] = 0;
      if (l == r)
      {
         seg[x] = ar[l];
         return;
      }
      int mid = (l + r) >> 1;
      create(l, mid, x + x + 1);
      create(mid + 1, r, x + x + 2);
      seg[x] = max(seg[x + x + 1], seg[x + x + 2]);
   }

   void lz_upd(int l, int r, int x) {
      if (lz[x] != 0) {
         seg[x] += lz[x];
         if (l != r)
         {
            lz[x + x + 1] += lz[x];
            lz[x + x + 2] += lz[x];
         }
         lz[x] = 0;
         return;
      }
   }
   void update_max (int ql, int qr, ll val) {
      upd(ql, qr, val, 0, sz - 1, 0);
   }

   ll query_max (int ql, int qr) {
      return get (ql, qr, 0, sz - 1, 0);
   }

   void upd(int ql, int qr, ll val, int l, int r, int x) {
      lz_upd(l, r, x);
      if (l > qr || r < ql) return;
      if (l >= ql && r <= qr) {
         seg[x] += val;
         if (l != r)
         {
            lz[x + x + 1] += val;
            lz[x + x + 2] += val;
         }
         return;
      }
      int mid = (l + r) >> 1;
      upd(ql, qr, val, l, mid, x + x + 1);
      upd(ql, qr, val, mid + 1, r, x + x + 2);
      seg[x] = max(seg[x + x + 1], seg[x + x + 2]);
   }

   ll get (int ql, int qr, int l, int r, int x) {
      lz_upd(l, r, x);
      if (l > qr || r < ql) return -inf;
      if (l >= ql && r <= qr) return seg[x];

      int mid = (l + r) >> 1;
      ll lq = get(ql, qr, l, mid, x + x + 1);
      ll rq = get(ql, qr, mid + 1, r, x + x + 2);
      return max(lq, rq);
   }
};

// DP on segments (using segment tree)
// Working on prefixes, dp[i] := max score possible of string of len 'i',
// such that s[i] = '1',
// Now the guess is the last 'j' (j < i) such that dp[j] + sum(seg[v].val) is
// maximum, where seg[v].val are all segment values which are taken in 'i' but
// not in 'j' i.e. seg[v].l <= i <= seg[v].r && (seg[v].l > j || seg[v].r < j)
//
// How to improve the running time? Use segment tree to get max, for each i
// remember which segments start here and which segments end here
// (use list of pairs(l, val))
// Iterate over all i, for each iteration we have to update the segment tree
// if we encounter a segment that starts at i, for each such segment
// starting at i, since we will have to add a segment in sum(seg[v].val) lets
// update the segment tree from [0 .. i-1] (which already contains dp values
// from [0...i-1]) by value of the cur segment, [ there are two type of
// segments in which i is contained, either the segment starts from i or
// started somewhere previously ], we updated all dp[j] (j < i) with
// dp[j] + sum(seg[v].val), Now max of this is dp[i], once we get dp[i]
// update the segment tree for i too, now since we will be moving to i + 1,
// before that update the segment tree by removing the values of segments that
// ends at i.
//
// Final answer max(dp[i])

const ll inf = (ll)1e18;

const int N = (int)2e5 + 10;
vector <vector <pii>> add, del;
int n, m;
ll dp[N];

void solve() { // O(NlogN)
   seg_max st(n);

   for (int i = 1; i <= n; ++i) {
      for (auto &p : add[i]) {
         int x = p.x, val = p.y;
         st.update_max(0, x, 1ll*val);
      }

      dp[i] = st.query_max(0, i - 1);
      st.update_max(i, i, dp[i]);

      for (auto &p : del[i]) {
         int x = p.x, val = p.y;
         st.update_max(0, x, -1ll*val);
      }
   }
   ll ans = 0;

   for (int i = 1; i <= n; ++i) {
      ans = max(ans, dp[i]);
   }
   cout << ans << '\n';
}

void read() {
   cin >> n >> m;
   add.assign(n + 1, vector <pii>());
   del.assign(n + 1, vector <pii>());

   for (int i = 0; i < m; ++i) {
      int l, r, a;
      cin >> l >> r >> a;
      add[l].emplace_back(l - 1, a);
      del[r].emplace_back(l - 1, a);
   }
}

signed main() {
   IOS; PREC;
   read();
   solve();

   return EXIT_SUCCESS;
}

