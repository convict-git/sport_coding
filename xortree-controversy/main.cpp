#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/detail/standard_policies.hpp>
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using ll = int64_t;
using ld = long double;
using ull = uint64_t;
using namespace std;
using namespace __gnu_pbds;
typedef vector <int> vi;
typedef pair <int, int> ii;

const int INF = 1 << 30;
const int maxn = 100010;
ll rev (ll n) {
    return INT_MAX ^ n;
}

int main() {
#ifdef BZ
    freopen("in.txt", "r", stdin); freopen("out.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr); cout.setf(ios::fixed); cout.precision(6);

    int n, k;
    cin >> n >> k;

    vector <ll> a (n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector <vi> adj (n + 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back (v);
        adj[v].push_back (u);
    }

    vector <vector <ll>> dp (n + 2, vector <ll> (17));
    vector <vector <ll>> temp (n + 2, vector <ll> (17));

    vi vis (n + 1);
    function <void (int, int)> dfs = [&] (int u, int v) {
        vis[u] = 1;
        for (auto el : adj[u]) {
            if (el != v) {
                dfs (el, u);
            }
        }
        int sz = adj[u].size();
        for (int i = 0; i <= sz; i++) {
            for (int j = 0; j <= k; j++) {
                temp[i][j] = LONG_LONG_MIN;
            }
        }
        for (int i = 0; i <= k; i++) {
            temp[0][i] = 0;
        }
        int childs_seen = 0;


        for (int i = 1; i <= sz; i++) {
            int el = adj[u][i - 1];
            if (el == v) {
                for (int j = 0; j <= k; j++) {
                    temp[i][j] = temp[i - 1][j];
                }
            } else {
               ++childs_seen;
               if (childs_seen == 1) {
                  for (int j = 0; j <= k; j++)  {
                     temp[i][j] = dp[el][j];
                  }
               }
                else {
                   for (int j = 0; j <= k; j++) {
                      for (int l = 0; j + l <= k; l++) {
                         temp[i][j + l] = max (temp[i][j + l], temp[i - 1][j] + dp[el][l]);
                      }
                   }
                }
            }
        }

        for (int i = 0; i <= k; i++) {
            dp[u][i] = temp[sz][i] + ((i & 1) ? rev (a[u]) : a[u]);
        }
    };

    dfs (0, -1);

    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            ans += a[i];
        }
    }

    cout << ans + dp[0][k] << "\n";


}
