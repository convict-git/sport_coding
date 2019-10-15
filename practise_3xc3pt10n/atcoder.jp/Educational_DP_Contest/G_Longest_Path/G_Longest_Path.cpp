#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ] "
#define x        first
#define y        second
using ll = long long;
using ff = long double;
using pii = pair<int,int>;

#define debug(args...) { \
/* WARNING : do NOT compile this debug func calls with following flags: // \
 * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) { it->empty();
   cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << fixed << setprecision(15) << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

const int N = (int)1e5 + 10;

vector < vector <int>> adj;
vector <int> order;
int dp[N];
bool vis[N];
int n, m;

void dfs (int u) {
   vis[u] = true;
   for (int v : adj[u]) if (!vis[v]) dfs (v);
   order.push_back(u);
}

void solve() {
   fill (vis, vis + n, false);
   fill (dp, dp + n, 0);
   for (int u = 0; u < n; ++u) if (!vis[u]) dfs (u);

   reverse(order.begin(), order.end());

   for (int u : order) {
      for (int v : adj[u]) dp[v] = max(dp[v], dp[u] + 1);
   }

   int mx_val = 0;
   for (int u : order) mx_val = max(mx_val, dp[u]);
   cout << mx_val << "\n";
}

void read() {
   cin >> n >> m;
   order.clear();
   adj.assign(n, vector <int> ());

   for (int e = 0; e < m; ++e) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      adj[u].push_back(v);
   }
}

signed main() {
   IOS; PREC;

   read(), solve();
   return EXIT_SUCCESS;
}
