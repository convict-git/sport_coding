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

const int N = (int)1e5 + 10;
int n;
vector <vector <int>> adj;
int f[N], g[N];

void root_at (int u, int pr, vector <bool>& vis)
{
   vis[u] = true;
   for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
      if (*it == pr)
      {
         adj[u].erase(it);
         break;
      }
   }
   for (int v : adj[u]) if (!vis[v]) root_at(v, u, vis);
}

void dfs (int u, vector <bool>&vis)
{
   vis[u] = true;
   f[u] = 0;
   g[u] = 0;

   vector <int> fval;
   for (int v : adj[u]) {
      if (!vis[v]) dfs(v, vis);
      f[u] = max(f[u], 1 + f[v]);
      fval.push_back(f[v]);
   }
   sort(fval.begin(), fval.end(), greater<int>());
   if ((int)fval.size() >= 2) {
      g[u] = 2 + fval[0] + fval[1];
   }
   else if ((int)fval.size() == 1) {
      g[u] = 1 + fval[0];
   }
}

void solve()
{
   vector <bool> vis(n, false);
   root_at(0, -1, vis);
   vis.assign(n, false);
   dfs(0, vis);

   int ans = 0;
   for (int i = 0; i < n; ++i) {
      ans = max(ans, g[i]);
   }
   cout << ans << '\n';
}

void read()
{
   cin >> n;
   adj.assign(n, vector <int> ());
   for (int i = 0; i < n - 1; ++i) {
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

