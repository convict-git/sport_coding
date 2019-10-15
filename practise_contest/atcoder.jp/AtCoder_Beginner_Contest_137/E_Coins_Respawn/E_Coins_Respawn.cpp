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
const int N = 2510;
const ll inf = (ll)1e18;
long long dist[N];
int Par[N];
int n, m, p;
vector <vector <pair <int, ll>>> Adj, AdjT;
bool from1[N], from2[N];

void dfs(int u, bool vis[], vector <vector <pair <int, ll> > > &Adj) {
   vis[u] = true;
   for (auto v_pair : Adj[u]) {
      int v = v_pair.x;
      if (!vis[v]) dfs(v, vis, Adj);
   }
}

bool spfa (int src, int target, bool print_path = false) {
   vector <int> inQueue (n, false);
   int cnt[N] = {0};
   for (int i = 0; i < N; ++i)
      Par[i] = -1, dist[i] = inf;

   queue <int> Q;
   Q.push(src);
   dist[src] = 0;
   inQueue[src] = true;

   while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      inQueue[u] = false;
      if (!(from1[u] && from2[u])) continue;

      for (auto vPair : Adj[u]) {
         int v = vPair.x;
         long long w = vPair.y;

         if (dist[u] != inf && dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            Par[v] = u;
            if (!inQueue[v]) {
               Q.push(v);
               inQueue[v] = true;
               ++cnt[v];
               if (cnt[v] > n) return false;
            }
         }
      }
   }
   return true;
}

signed main() {
   IOS; PREC;
   cin >> n >> m >> p;
   Adj.assign(n, vector <pair <int, ll>>());
   AdjT.assign(n, vector <pair <int, ll>>());
   fill(from1, from1 + n, false);
   fill(from2, from2 + n, false);
   for (int e = 0; e < m; ++e) {
      int u, v, Ci;
      cin >> u >> v >> Ci;
      --u, --v;
      Adj[u].emplace_back(v, -1ll*(Ci - p));
      AdjT[v].emplace_back(u, -1ll*(Ci - p));
   }
   dfs(0, from1, Adj), dfs(n - 1, from2, AdjT);
   bool ok = spfa(0, n - 1);
   if (ok) {
      ll ans = max(0ll, -1*dist[n - 1]);
      cout << ans << '\n';
   }
   else cout << - 1 << '\n';

   return EXIT_SUCCESS;
}
