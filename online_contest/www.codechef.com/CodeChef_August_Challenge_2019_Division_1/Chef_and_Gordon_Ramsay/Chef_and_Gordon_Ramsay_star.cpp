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

const int infi = (int)1e9;
vector <vector <int> > adj;
vector <int> deg;
bool star;
int n, root, p[4];

void read() {
   cin >> n;

   adj.assign(n, vector <int> ());
   deg.assign(n, 0);

   for (int i = 1; i <= 3; ++i) {
      cin >> p[i];
   }
   for (int e = 0; e < n - 1; ++e) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      adj[u].push_back(v);
      adj[v].push_back(u);
      ++deg[u], ++deg[v];
   }
   for (int u = 0; u < n; ++u) {
      if (deg[u] == n - 1) {
         star = true;
         root = u;
         break;
      }
   }
}

void solve() {
   int a2 = root;
   ll ans = 0;
   // chose a1 and a3

   for (int a1 : adj[a2]) {
      if ((a1 < a2 && p[1] < p[2]) || (a1 > a2 && p[1] > p[2])) {
         int lower, upper;
         if (p[3] > max(p[2], p[1])) {
            lower = max(a2, a1);
            upper = infi;
            ans += (n - lower - 1);
         }
         else if (p[3] < min(p[1], p[2])) {
            lower = -infi;
            upper = min(a2, a1);
            ans += (upper - 1 + 1);
         }
         else {
            lower = min(a2, a1);
            upper = max(a2, a1);
            ans += (upper - lower - 1);
         }
      }
   }
   cout << ans << '\n';
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      star = false;
      read();
      if (star) {
         solve();
      }
      else cout << -1 << '\n';
   }

   return EXIT_SUCCESS;
}
