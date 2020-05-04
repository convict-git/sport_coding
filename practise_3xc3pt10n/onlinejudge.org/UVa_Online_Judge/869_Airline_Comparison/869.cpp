#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;

const int N = 26;
int m;
bool W[2][N][N];

void transitiveClosure() {
   for (int k = 0; k < N; ++k)
      for (int i = 0; i < N; ++i)
         for (int j = 0; j < N; ++j)
            for (int f = 0; f < 2; ++f)
               W[f][i][j] |= (W[f][i][k - 1] && W[f][k - 1][j]);
}

bool solve() {
   transitiveClosure();

   for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
         if (W[0][i][j] ^ W[1][i][j]) return false;
      }
   }
   return true;
}

void read() {
   for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
         for (int f = 0; f < 2; ++f)
            W[f][i][j] = false;

   string u, v;
   cin >> m;
   for (int i = 0; i < m; ++i) {
      cin >> u >> v;
      W[0][u[0] - 'A'][v[0] - 'A'] = true;
   }
   cin >> m;
   for (int i = 0; i < m; ++i) {
      cin >> u >> v;
      W[1][u[0] - 'A'][v[0] - 'A'] = true;
   }
}

signed main() {
   int tc;
   cin >> tc;
   for (int i = 0; i < tc;) {
      if (i) cout << '\n';
      ++i;
      read();
      cout << (solve() ? "YES\n" : "NO\n");
   }

   return EXIT_SUCCESS;
}

