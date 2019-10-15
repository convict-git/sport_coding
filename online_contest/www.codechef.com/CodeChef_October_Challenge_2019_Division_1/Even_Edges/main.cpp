#include <bits/stdc++.h>
using namespace std;

int main() {
   int tc;
   cin >> tc;
   while (tc--) {
      int n, m;
      cin >> n >> m;
      vector <int> deg(n);
      vector <vector <int>> T(n, vector <int> ());
      for (int i = 0; i < m; ++i) {
         int u, v; cin >> u >> v;
         --u, --v;
         ++deg[u], ++deg[v];
         T[u].push_back(v);
         T[v].push_back(u);
      }
      vector <int> part(n, 1);
      if (m % 2 == 0) {
         cout << 1 << '\n';
      }
      else {
         bool odd = false;
         for (int i = 0; i < n; ++i) if (deg[i] & 1) {
            odd = true;
            cout << 2 << '\n';
            part[i] = 2;
            break;
         }
         if (!odd) {
            int odd_one = -1;
            for (int i = 0; i < n; ++i) {
               if (deg[i] > 0) {
                  odd_one = i;
                  part[odd_one] = 1;
                  for (int v : T[odd_one]) --deg[v];
                  break;
               }
            }
            int j = 1;
            for (int i = 0; i < n; ++i) {
               if (i != odd_one && (deg[i] & 1)) {
                  part[i] = 2;
                  ++j;
                  break;
               }
            }
            for (int i = 0; i < n; ++i) if (i != odd_one && part[i] != 2) {
               part[i] = 3;
               if (j == 2) ++j;
            }
            cout << j << '\n';
         }
      }
      for (int i = 0; i < n; ++i) {
         cout << part[i] << ' ';
      }
      cout << '\n';
   }
   return 0;
}
