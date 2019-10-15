#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;

const int N = 105;
const int infi = (int)1e9;
const long long inf = (long long)1e18;

int n, m, s, k1, k2;
int W[N][N];
vector <int> S;

void floydWarshall() {
   for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            if (W[i][k] < infi && W[k][j] < infi)
               W[i][j] = W[j][i] = min(W[i][j], W[i][k] + W[k][j]);
}

inline int fac(int num) { return (num == 0 ? 1 : fac(num - 1) * num); }

void solve() {
   floydWarshall();

   int totalPerm = fac(s);
   long long mnDist = inf;

   for (int it = 0; it < totalPerm; ++it) {
      if (it) next_permutation(S.begin(), S.end());

      long long dk1[9], dk2[9];
      dk2[s] = dk1[0] = 0;


      for (int i = 1; i <= s; ++i) {
         if (i == 1) dk1[i] = W[k1][S[i - 1]];
         else dk1[i] = dk1[i - 1] + 1ll * W[S[i - 2]][S[i - 1]];
      }

      for (int i = s - 1; i >= 0; --i) {
         if (i == s - 1) dk2[i] = W[k2][S[i]];
         else dk2[i] = dk2[i + 1] + 1ll * W[S[i + 1]][S[i]];
      }

      for (int i = 0; i <= s; ++i) {
         mnDist = min(mnDist, dk1[i] + dk2[i]);
      }
   }
   cout << mnDist << '\n';
}

void read() {
   cin >> m;
   int u, v, c;
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j)
         W[i][j] = (i == j ? 0 : infi);

   for (int i = 0; i < m; ++i) {
      cin >> u >> v >> c;
      W[u][v] = W[v][u] = c;
   }

   cin >> s;
   S.clear();
   for (int i = 0; i < s; ++i) {
      cin >> u;
      S.push_back(u);
   }

   cin >> k1 >> k2;
}

signed main() {
   while (cin >> n) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

