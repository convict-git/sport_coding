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

const int N = (int)5e4 + 10, K = 504;
int f[N][K], g[N][K], pref[N][K];
int mx[N];
int n, k;
vector < vector <int> > adj;
vector <bool> vis;

void root_at(int u, int pr)
{
   vis[u] = true;
   mx[u] = 0;
   for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
      if (*it == pr) {
         adj[u].erase(it);
         break;
      }
   }
   for (int v : adj[u])
      if (!vis[v])
         root_at(v, u), mx[u] = max(mx[u], 1 + mx[v]);
}

vector <int> order;
void dfs_order(int u) {
   vis[u] = true;
   for (int v : adj[u]) if (!vis[v]) dfs_order(v);
   order.push_back(u);
}

void solve()
{
   vis.assign(n, false);
   root_at(0, -1);
   vis.assign(n, false);
   dfs_order(0);

   for (int u : order) {
      int nc = (int)adj[u].size();

      // vector <vector <int>> pref(nc, vector <int>(k+1));
      // // This is shit//never use vectors for dp

      for (int j = 0; j <= k; ++j)
         f[u][j] = g[u][j] = 0;

      f[u][0] = 1;

      for (int j = 1, real_j; j <= k; ++j) {
         if (j > 2*mx[u]) break;

         //calc f[u],,one edge already reserved
         int total_f = 0;
         real_j = j - 1;
         if (j >= 1) {
            for (int v : adj[u]) {
               total_f += f[v][real_j];
            }
         }
         f[u][j] = total_f;

         //calc g[u],,two edges already reserved
         int total_g = 0;
         real_j = j - 2;
         if (j >= 2) {
            for (int i = 0; i < nc; ++i) {
               int v = adj[u][i];
               if (i == 0) {
                  pref[i][real_j] = f[v][real_j];
                  continue;
               }
               pref[i][real_j] = pref[i-1][real_j] + f[v][real_j];
               for (int x = 0; x <= real_j;  ++x) {
                  total_g += pref[i-1][real_j-x] * f[v][x];
               }
            }
         }
         g[u][j] = total_g;
      }
   }

   int total = 0;
   for (int i = 0; i < n; ++i) {
      total = total + f[i][k] + g[i][k];
   }
   cout << total << '\n';
}

void read()
{
   cin >> n >> k;
   adj.assign(n, vector<int> ());
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
}
