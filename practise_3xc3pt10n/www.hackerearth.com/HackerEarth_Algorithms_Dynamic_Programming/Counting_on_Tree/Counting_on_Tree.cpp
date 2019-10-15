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

const int N = (int)1e5 + 10, K = 104;
const int MOD = (int)1e9 + 7;
int n, k;
vector <vector <int>> adj;
int ar[N], mx[N];
int dp[N][K];
int pref[N][K];

inline int add (int a, int b) {
   return (a + b) % MOD;
}
inline int mul (int a, int b) {
   return int(1ll*a*b % MOD);
}

void root_at(int u, int pr, vector <bool>&vis) {
   vis[u] = true;
   mx[u] = ar[u];
   for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
      if (*it == pr)
      { adj[u].erase(it);
         break;
      }
   }
   for (int v : adj[u])
      if (!vis[v])
         root_at(v, u, vis), mx[u] += mx[v];
}
#define fr(i,x,y) for(int i = x; i <= y; ++i)

void dfs (int u, vector <bool>&vis) {
   vis[u] = true;
   int nc = (int)adj[u].size();
   for (int i = 0; i <= k; ++i)
      dp[u][i] = 0;
   dp[u][ar[u]] = 1;

   for (int v : adj[u])
      if (!vis[v]) dfs(v, vis);

   // vector <vector <int>> pref(nc, vector <int>(k+1));
   for (int j = 0; j <= k; ++j) {
      int real_j = (ar[u] ? j-1 : j);
      if (real_j == -1) continue;
      if (j > mx[u]) break;

      for (int i = 0; i < nc; ++i) {
         int v = adj[u][i];
         if (i == 0) {
            int rval = add(dp[v][real_j], (!real_j ? 1 : 0));
            // if you want sum 0 from this child one option is also to not chose the child at all
            pref[i][real_j] = rval;
         }
         else {
            for (int x = 0; x <= real_j; ++x) {
               int rval = add(dp[v][x], (!x ? 1 : 0));
               // if you want sum 0 from this child one option is also to not chose the child at all
               pref[i][real_j] = add(pref[i][real_j], mul(pref[i - 1][real_j - x], rval));
            }
         }
      }
      if (nc != 0) {
         dp[u][j] = pref[nc-1][real_j];
      }
   }
}

void solve() {
   vector <bool> vis(n, false);
   root_at(0, -1, vis);

   vis.assign(n, false);
   dfs(0, vis);

   int total = 0;
   for (int i = 0; i < n; ++i)
      total = add(total, dp[i][k]);
   cout << total << '\n';
}

void read() {
   cin >> n >> k;
   adj.assign(n, vector <int>());
   for (int i = 0; i < n; ++i)
      cin >> ar[i], mx[i] = 0;
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
   int tc;
   cin >> tc;
   while (tc--) read(), solve();

   return EXIT_SUCCESS;
}
