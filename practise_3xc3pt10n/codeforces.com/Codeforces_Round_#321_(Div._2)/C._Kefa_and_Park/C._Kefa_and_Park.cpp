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
const int N = (int)1e5 + 1;

int n, m;

vector <vector <int> > adj;
int dp[N];
bool is_cat[N] = {false};

int ans = 0;	// final number of restaurants where he can go

void root_at(int u, int pr) {
   for(int i = 0; i < (int)adj[u].size(); ++i){
      if (adj[u][i] == pr) {
         adj[u].erase(adj[u].begin() + i);
         break;
      }
   }
   for (int v : adj[u])
      root_at(v, u);
}

void dfs(int u) {
   if (dp[u] > m) return;
   for (int v : adj[u]) {
      if (is_cat[v]) dp[v] = dp[u] + 1;
      else dp[v] = 0;
      dfs(v);
   }
   if ((int)adj[u].size() == 0) ++ans;
}

void read() {
   cin >> n >> m;
   adj.assign(n, vector <int>());
   fill (is_cat, is_cat + n, false);

   for (int i = 0; i < n; i++) {
      cin >> is_cat[i];
   }
   for (int i = 0, u, v; i < n - 1; i++) {
      cin >> u >> v;
      --u, --v;
      adj[u].push_back(v);
      adj[v].push_back(u);
   }
}

void solve() {
   ans = 0;
   dp[0] = is_cat[0];
   root_at(0, -1);
   dfs(0);
   cout << ans << '\n';
}

signed main() {
   read(), solve();
   IOS; PREC;

   return EXIT_SUCCESS;
}
