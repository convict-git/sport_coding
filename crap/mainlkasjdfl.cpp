#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int,int>;

int main () {
  int n, m;
  cin >> n >> m;
  vector <int> w(n);
  for (int i = 0; i < n; ++i) {
    cin >> w[i];
  }
  int u, v;
  vector<vector <int>> T(n, vector<int>());
  for (int i = 0; i < m; ++i){
    cin >> u >> v;
    --u, --v;
    T[u].push_back(v);
    T[v].push_back(u);
  }
  int s;
  cin >> s;
  --s;

  vector <bool> vis(n, false);
  vector <int> order;
  function <void(int)> dfs = [&] (int u) -> void {
    vis[u] = true;
    for (int v : T[u]) if (!vis[v]) dfs(v);
    order.push_back(u);
  };
  dfs(s);
  vector <ll> dp(n);
  for (int i = 0; i < n; ++i)
    dp[i] = w[i];

  for (int u : order) {
    for (int v : T[u]) {
      dp[v] = max(dp[v], dp[v] + dp[u]);
    }
  }
  cout << dp[s] << '\n';
}
