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

const int N = (int)1e5 + 10, Mod = (int)1e9 + 7;
int p, q, r;
int pa[N], qa[N], ra[N], fp[N], fr[N];

int add (int x, int y) {
   return (x + y) % Mod;
}
int mul (int x, int y) {
   return int(1ll * x * y % Mod);
}

void read() {
   cin >> p >> q >> r;
   for (int i = 0; i < p; ++i) cin >> pa[i];
   for (int i = 0; i < q; ++i) cin >> qa[i];
   for (int i = 0; i < r; ++i) cin >> ra[i];

   sort (pa, pa + p);
   sort (qa, qa + q);
   sort (ra, ra + r);

   for (int i = 0; i < p; ++i)  {
      if (i == 0) fp[i] = pa[i];
      else fp[i] = add(fp[i - 1], pa[i]);
   }
   for (int i = 0; i < r; ++i)  {
      if (i == 0) fr[i] = ra[i];
      else fr[i] = add(fr[i - 1], ra[i]);
   }
}

#define fr(i,x,y) for(int i = x; i <= y; ++i)
void solve() {
   int ans = 0;
   for (int i = 0, l, h; i < q; ++i) { // fixing Y
      int Y = qa[i], X, Z, x_idx, z_idx;
      l = 0, h = p - 1;
      while (l <= h) { // finding max index such that pa[i] <= Y
         int g = (l + h)/2;
         X = pa[g];
         if (X <= Y) l = g + 1;
         else h = g - 1;
      }
      if (h == -1) continue;
      x_idx = h;

      l = 0, h = r - 1;
      while (l <= h) { // finding max index such that ra[i] <= Y
         int g = (l + h)/2;
         Z = ra[g];
         if (Z <= Y) l = g + 1;
         else h = g - 1;
      }
      if (h == -1) continue;
      z_idx = h;

      int x_val = add(mul(Y, x_idx + 1), fp[x_idx]);
      int z_val = add(mul(Y, z_idx + 1), fr[z_idx]);
      ans = add(ans, mul(x_val, z_val));
   }
   cout << ans << '\n';
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
