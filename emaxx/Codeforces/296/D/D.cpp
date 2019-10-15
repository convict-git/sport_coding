#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;

const int N = 505;
const int infi = (int)1e9;
const long long inf = (long long)1e18;

int n;
int tmp[N][N], mp[N];
int W[N][N];
long long cost[N + 1];

void modFloydWarshall() {
   for (int k = n; k >= 1; --k) {
      cost[k] = 0;

      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            W[i][j] = min(W[i][j], W[i][k - 1] + W[k - 1][j]);

      for (int i = 0; i < n; ++i) {
         for (int j = 0; j < n; ++j) {
            if (i < k - 1 || j < k - 1) continue;
            cost[k] += 1ll*W[i][j];
         }
      }
   }
}

void solve() {
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         W[i][j] = tmp[mp[i]][mp[j]];
   modFloydWarshall();

   for (int k = 1; k <= n; ++k) {
      cout << cost[k] << " \n"[k == n];
   }
}

void read() {
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
         cin >> tmp[i][j];
      }
   }
   for (int i = 0; i < n; ++i) {
      cin >> mp[i];
      --mp[i];
   }
}

signed main() {
   IOS; PREC;
   while (cin >> n) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}
