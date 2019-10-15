#include         <bits/stdc++.h>
using namespace std;
#ifndef CONVICTION
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ] "
#define x        first
#define y        second
using ll = long long;
using ff = long double;
using pii = pair<int,int>;

#define debug(args...) \
{ \
/* WARNING : do NOT compile this debug func calls with following flags: // \
 * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); \
   istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it)
{
   it->empty(); cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args)
{
	cerr << fixed << setprecision(15)
      << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

const int N = (int)1e5 + 10, K = 200;
const ll inf = (ll)1e18;
ll dp[N][K];
int n, k;
int cnt[N];
ll w[N];
vector <vector<int>> adj;

void root_at(int u, int pr, vector <bool> &vis)
{
   vis[u] = true;
   for (auto vit = adj[u].begin(); vit != adj[u].end(); ++vit) {
      if (*vit == pr)
      {
         adj[u].erase(vit);
         break;
      }
   }
   for (int v : adj[u])
      if (!vis[v]) root_at(v, u, vis);
}

void dfs_freq(int u, vector <bool> &vis)
{
   vis[u] = true;
   cnt[u] = 1;
   for (int v : adj[u]) {
      if (!vis[v])
      {
         dfs_freq(v, vis);
         w[u] += w[v];
         cnt[u] += cnt[v];
      }
   }
}

void dfs (int u, vector <bool> &vis)
{
   vis[u] = true;
   int nchild = (int)adj[u].size();
   vector <vector<ll>> pref(nchild, vector <ll> (k+1));
   dp[u][0] = 0;

   for (int rem = 1; rem <= k; ++rem) {
      if (rem > cnt[u]) dp[u][rem] = inf;
      else dp[u][rem] = w[u];
   }

   for (int v : adj[u]) {
      if (!vis[v]) dfs(v, vis);
   }

   for (int rem = 0; rem <= k; ++rem) {
      if (rem > cnt[u]) break; // very important
      for (int i = 0; i < (int)adj[u].size(); ++i) {
         int v = adj[u][i];
         if (i == 0) {
            pref[i][rem] = dp[v][rem];
         }
         else {
            for (int x = 0; x <= rem; ++x) {
               if (pref[i-1][rem-x] != inf && dp[v][x] != inf)
                  pref[i][rem] = min(pref[i][rem], pref[i-1][rem-x] + dp[v][x]);
            }
         }
      }
      if (adj[u].size())
         dp[u][rem] = min(pref[adj[u].size()-1][rem], dp[u][rem]);
   }
}

void solve()
{
   vector <bool> vis(n, false);
   root_at(0, -1, vis);
   vis.assign(n, false);
   dfs_freq(0, vis);

   vis.assign(n, false);
   dfs(0, vis);
   ll ans = 0;
   for (int i = 0; i <= k; ++i) {
      ans = min(ans, dp[0][i]);
   }
   cout << w[0] - ans << '\n';
}

void read()
{
   cin >> n >> k;
   adj.assign(n, vector <int> ());

   for (int i = 0; i < n; ++i)
      cin >> w[i];

   for (int i = 0; i < n - 1; ++i)
   {
      int u, v;
      cin >> u >> v;
      --u, --v;
      adj[u].push_back(v);
      adj[v].push_back(u);
   }
}

signed main()
{
   IOS; PREC;
   read(), solve();

   return EXIT_SUCCESS;
}
