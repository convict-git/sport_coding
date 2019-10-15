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
#define x     first
#define y     second
#define bg(x) " [ " << #x << " : " << (x) << " ] "
#define un(x) sort(x.begin(), x.end()), \
              x.erase(unique(x.begin(), x.end()), x.end())
using   ll  = long long;
using   ull = unsigned long long;
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

seed_seq seq{
   (uint64_t) chrono::duration_cast<chrono::nanoseconds>
      (chrono::high_resolution_clock::now().time_since_epoch()).count(),
      (uint64_t) __builtin_ia32_rdtsc(),
      (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]

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
/*****************************************************************************/

#include <bits/stdc++.h>
using namespace std;
struct seg_max {
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
      seg[x] = min(seg[x + x + 1], seg[x + x + 2]);
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

vector <pii> p;
int n;
const int N = (int)1e6 + 10;

void read() {
   cin >> n;
   p.assign(n, pii());
   for (int i = 0; i < n; ++i) {
      cin >> p[i].x >> p[i].y;
   }
}

void solve() {
   seg_max st(100);
   for (int i = 0; i < n; ++i) {
      st.update_max(p[i].x, p[i].y, 1);
   }

   int cnt = 0;
   for (int i = 0; i < n; ++i) {
      int q = st.query_max(p[i].x, p[i].y);
      if (q == 1) ++cnt;
      st.update_max(p[i].x, p[i].y, -1);
   }
   cout << cnt << '\n';
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      read(), solve();
   }

   return EXIT_SUCCESS;
}

