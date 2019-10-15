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

const int N = 6004;
int con[N];
int g[N], f[N], indeg[N];
vector <vector<int>> adj;
int n;

void dfs(int u, vector <bool> &vis)
{
   vis[u] = true;
   g[u] = 0, f[u] = con[u];

   for (int v : adj[u]) {
      if (!vis[v]) dfs(v, vis);
      g[u] += max(g[v], f[v]);
      f[u] += g[v];
   }
}

void solve()
{
   int pres = -1;
   for (int i = 0; i < n; ++i) {
      if (indeg[i] == 0)
      {
         pres = i;
         break;
      }
   }
   assert(pres != -1);

   vector <bool> vis(n, false);
   dfs(pres, vis);
   cout << max(f[pres],g[pres]) << '\n';
}

void read()
{
   cin >> n;
   adj.assign(n, vector <int> ());
   for (int i = 0; i < n; ++i)
      cin >> con[i], indeg[i] = 0;

   for (int i = 0; i < n - 1; ++i) {
      int u, v;
      cin >> v >> u;
      --u, --v;
      ++indeg[v];
      adj[u].push_back(v);
   }

}

signed main()
{
   IOS; PREC;
   read(), solve();

   return EXIT_SUCCESS;
}
