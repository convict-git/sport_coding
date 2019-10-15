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

const int N = (int)1e5 + 10;
int n, q;
int ai[N], aj[N], ak[N];

class seg_tree  {
   bool seg[4 * N];
   public:
   seg_tree() {
      for (int i = 0; i < 4 * N; ++i) seg[i] = false;
   }

   void upd (int l, int r, int x, int &val) {
      if (l == r) {
         if (val == l) {
            seg[x] = true; }
         return;
      }
      if (l > val || r < val) return;
      int mid = (l + r)/2;
      if (val >= l && val <= mid)
         upd (l, mid, x + x + 1, val);
      else if (val >= mid + 1 && val <= r)
         upd (mid + 1, r, x + x + 2, val);
      seg[x] |= (seg[x + x + 1] | seg[x + x + 2]);
   }

   int qry (int l, int r, int x, int &val) {
      // debug(l, r, x , val);
      if (!seg[x] || l > val) return 0;
      int mid = (l + r)/2;
      if (r < val) {
         if (l == r) { //ans found
            if (seg[x]) return l;
            else return 0;
         }
         if (seg[x + x + 2]) { //prefer right
            return qry(mid + 1, r, x + x + 2, val);
         }
         else if (seg[x + x + 1]) { //right not exist so check left
            return qry (l, mid, x + x + 1, val);
         }
         else return 0;
      }
      else {
         if (l == r) { // key point of seg tree
            if (seg[x]) return l;
            else return 0;
         }
         else if (val <= mid) {
            return qry(l, mid, x + x + 1, val);
         }
         else {
            int lqry = qry(l, mid, x + x + 1, val);
            int rqry = qry(mid + 1, r, x + x + 2, val);
            return max(lqry, rqry);
         }
      }
   }

   int query (int &val) { return qry (0, N, 0, val); }
   void update (int &val) { upd(0, N, 0, val); }
};

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      cin >> n >> q;
      seg_tree prefix, suffix;
      for (int i = 0; i < n; ++i) {
         cin >> aj[i];
      }

      for (int i = 0; i < n; ++i) {
         ai[i] = prefix.query(aj[i]);
         prefix.update(aj[i]);
      }
      for (int i = n - 1; i >= 0; --i) {
         ak[i] = suffix.query(aj[i]);
         suffix.update(aj[i]);
      }

      while (q--) {
         int idx;
         cin >> idx;
         --idx;
         cout << 1ll*aj[idx] * ai[idx] * ak[idx] << '\n';
      }
   }

   return EXIT_SUCCESS;
}
