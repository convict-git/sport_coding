#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (6); cout << fixed
#define x        first
#define y        second
using namespace std;

const int N = 105;
const int MAXR = 10010;
const int infi = (int)1e9;

int n, R, q;
int W[N][N];
long double P[N][MAXR];

void floydWarshall () {
   for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            if (W[i][k] < infi && W[k][j] < infi)
               W[j][i] = W[i][j] = min (W[i][j], W[i][k] + W[k][j]);
}

void calcProbDP() {
   long double invR = 1.0 / R;

   for (int i = 0; i <= n; ++i)
      for(int j = 0; j <= 100 * R; ++j)
         P[i][j] = 0;

   for (int i = 0; i <= 100 * R; ++i)
      P[0][i] = 0;

   P[0][0] = 1.0;

   for (int i = 1; i <= n; ++i)
      for (int Y = 1; Y <= R; ++Y)
         for (int X = Y; X <= 100 * R; ++X)
            P[i][X] += P[i - 1][X - Y] * invR;
}

void solve(int tc) {
   floydWarshall();
   calcProbDP();

   cin >> q;
   int u, v, budget;
   cout << "Case " << tc << '\n';
   while (q--) {
      cin >> u >> v >> budget;
      --u, --v;
      int d = W[u][v];

      long double totalProb = 0;

      for (int i = 1; i <= budget; ++i) {
         totalProb += P[d][i];
      }
      assert(totalProb < 1.0 + 1e-9);

      cout << totalProb << '\n';
   }
}

void read() {
   cin >> n >> R;
   for (int i = 0; i < n; ++i) {
      string s;
      cin >> s;
      assert ((int)s.size() == n);
      for (int j = 0; j < n; ++j) {
         if (s[j] == 'N') W[i][j] = W[j][i] = infi;
         else if (s[j] == 'Y') W[i][j] = W[j][i] = 1;
         else assert (false);
      }
   }
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   for (int i = 0; i < tc; ) {
      if (i) cout << '\n';
      ++i;
      read();
      solve(i);
   }
   return EXIT_SUCCESS;
}

