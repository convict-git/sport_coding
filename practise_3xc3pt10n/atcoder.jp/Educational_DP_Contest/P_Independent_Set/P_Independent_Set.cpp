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

const int N = (int)1e5 + 10, MOD = (int)1e9 + 7;
vector <vector <int>> adj;
int n, m;
int dp[N], exc[N];
bool vis[N];

int mul (int a, int b) {
   return int((1ll *(a%MOD) * (b%MOD))%MOD);
}
int add (int a, int b) {
   return ((a%MOD) + (b%MOD))%MOD;
}

void dfs(int u, int pr) {
   vis[u] = true;
   for (int v : adj[u])
      if (v != pr && !vis[v]) dfs(v, u);

   int dp_mul = 1, exc_mul = 1;
   for (int v : adj[u]) {
      if (v == pr) continue;
      dp_mul = mul(dp_mul, dp[v]);
      exc_mul = mul(exc_mul, exc[v]);
   }
   dp[u] = add(dp_mul, exc_mul);
   exc[u] = dp_mul;
   return;
}

void solve() {
   for (int i = 0; i < n; ++i) vis[i] = 0;
   dfs(0, -1);

   cout << dp[0] << '\n';
}

signed main() {
   IOS; PREC;
   cin >> n;
   m = n - 1;
   adj.assign(n, vector <int> ());
   for (int e = 0; e < m; ++e) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      adj[u].push_back(v);
      adj[v].push_back(u);
   }
   solve();

   return EXIT_SUCCESS;
}
