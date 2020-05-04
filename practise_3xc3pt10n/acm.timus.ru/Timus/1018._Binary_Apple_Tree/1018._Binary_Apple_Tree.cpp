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

const int N = 105;
int n, q;
int new_x = 0;
vector <vector <pii>> adj, ed;
int apples[N], cnt[N];
int dp[N][N]; // max apples

void root_at(int u, int pr, vector <bool> &vis,
    vector <vector <pii>> &G) {
  vis[u] = true;
  for (auto vit = G[u].begin(); vit != G[u].end(); ++vit) {
    if ((*vit).x == pr) {
      G[u].erase(vit);
      break;
    }
  }
  for (pii v_pair : G[u]) {
    int v = v_pair.x;
    if (!vis[v])
      root_at(v, u, vis, G);
  }
}

void dfs_cnt(int u, vector <bool>&vis) {
  vis[u] = true;
  cnt[u] = 1;
  for (auto v_pair : ed[u]) {
    int v = v_pair.x;
    if (!vis[v]) dfs_cnt(v, vis);
    cnt[u] += cnt[v];
  }
}

void create(int u, int x, vector <bool> &vis) {
  vis[u] = true;
  for (int i = 0; i < (int)adj[u].size(); ++i) {
    int v = adj[u][i].x;
    if (!vis[v]) {
      ++new_x;
      assert(new_x <= n);

      ed[x].push_back(pii(new_x, 0));
      ed[new_x].push_back(pii(x, 0));

      apples[new_x] = adj[u][i].y;
      create(v, new_x, vis);
    }
  }
}

void dfs(int u, vector <bool> &vis) {
  vis[u] = true;
  int nchild = (int)ed[u].size();
  vector <vector <int>> pref(nchild, vector <int>(q+1));
  for (auto v_pair : ed[u]) {
    int v = v_pair.x;
    if (!vis[v])
      dfs(v, vis);
  }


  for (int i = 0; i <= q; ++i)
    dp[u][q] = 0;
  dp[u][1] = apples[u];

  for (int j = 0; j < q; ++j) {
    if (j > cnt[u] - 1) break;

    for (int i = 0; i < nchild; ++i) {
      int v = ed[u][i].x;
      if (i == 0) {
        for (int x = 0; x <= j; ++x)
          pref[i][x] = dp[v][x];
      }
      else {
        for (int x = 0; x <= j; ++x)
          pref[i][j] = max(pref[i][j], pref[i-1][j-x] + dp[v][x]);
      }
    }
    if (nchild != 0)
      dp[u][j + 1] = max(dp[u][j + 1], apples[u] + pref[nchild-1][j]);
  }

}

void solve() {
  vector <bool> vis(n + 1, false);
  root_at(0, -1, vis, adj);

  vis.assign(n, false);
  create(1, 0, vis);

  vis.assign(n, false);
  root_at(0, -1, vis, ed);

  vis.assign(n, false);
  dfs_cnt(0, vis);

  vis.assign(n, false);
  dfs(0, vis);


  cout << dp[0][q] << '\n';
}


void read() {
  cin >> n >> q;
  ++q;
  adj.assign(n + 1, vector <pii> ());
  ed.assign(n + 1, vector <pii> ());
  adj[0].push_back(pii(1, 0));


  for (int i = 0; i < n - 1; ++i) {
    int u, v, val;
    cin >> u >> v >> val;
    adj[u].push_back(pii(v, val));
    adj[v].push_back(pii(u, val));
  }
}

signed main()
{
  IOS; PREC;
  read(), solve();
  return EXIT_SUCCESS;
}
