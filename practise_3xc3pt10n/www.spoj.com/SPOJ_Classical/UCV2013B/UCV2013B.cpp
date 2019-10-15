#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    "[ " << #x << " : " << x << " ]"
#define x        first
#define y        second
using namespace std;

const int N = 105;
const long long inf = (long long)1e18;

int n, q;
long long W[N][N];
map <int, string> mp;

void floydWarshall() {
   for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            if (W[i][k] < inf && W[k][j] < inf)
               W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
}

void solve(int tc) {
   floydWarshall();
   cout << "Case #" << tc << ":\n";
   cin >> q;
   int u, v;
   while (q--) {
      cin >> u >> v;
      if (W[u][v] == inf)
         cout << mp[u] << '-' << mp[v] << " NOT REACHABLE\n";
      else if (W[u][u] < 0 || W[v][v] < 0)
         cout << "NEGATIVE CYCLE\n";
      else cout << mp[u] << '-' << mp[v] << ' ' << W[u][v] << '\n';
   }
}

void read() {
   mp.clear();
   string s;
   long long w;
   for (int i = 0; i < n; ++i) {
      cin >> s;
      mp[i] = s;
      for (int j = 0; j < n; ++j) {
         cin >> w;
         if (i == j && w > 0) w = 0;
         else if (i != j && w == 0) w = inf;
         W[i][j] = w;
      }
   }
}

signed main() {
   int tc = 0;
   while (cin >> n, n) {
      ++tc;
      read();
      solve(tc);
   }

   return EXIT_SUCCESS;
}

