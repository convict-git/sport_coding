#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (3); cout << fixed
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = 205;
const long double eps = 1e-9;
int n;
long double W[N][N];
pii point[N];

inline long double dist(int u, int v) {
   return hypot(point[u].x - point[v].x, point[u].y - point[v].y);
}

void modFloydWarshall() {
   for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            W[i][j] = W[j][i] = min(W[i][j], max(W[i][k], W[k][j]));
}

void read() {
   int tc = 0;
   while (cin >> n, n) {
      ++tc;
      for (int i = 0; i < n; ++i)
         cin >> point[i].x >> point[i].y;

      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            W[i][j] = W[j][i] = dist(i, j);

      modFloydWarshall();
      cout << "Scenario #" << tc << "\n";
      cout << "Frog Distance = " << W[0][1] << '\n' << '\n';
   }
}

signed main() {
   IOS; PREC;
   read();

   return EXIT_SUCCESS;
}
