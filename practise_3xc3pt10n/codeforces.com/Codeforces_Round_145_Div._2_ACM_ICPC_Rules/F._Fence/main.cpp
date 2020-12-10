#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

void preproc() {
}

void solve() {
   int n, a, b;
   cin >> n >> a >> b;
   vector <int> h(n);
   int sm = 0;
   for (int i = 0; i < n; ++i) {
      cin >> h[i];
      sm += h[i];
   }

   vector <vector <int>> red;
   vector <vector <int>> gre;
   red.assign(n, vector <int> (a + 1, INT_MAX));
   gre.assign(n, vector <int> (a + 1, INT_MAX));

   red[0][h[0]] = 0;
   gre[0][0] = 0;

   for (int pos = 1; pos < n; ++pos) {
      for (int area = 0; area <= a; ++area) {
         // upd red[pos][area]
         int &r = red[pos][area];
         if (area - h[pos] >= 0) {
            if (red[pos - 1][area - h[pos]] < INT_MAX) {
               r = min(r, red[pos - 1][area - h[pos]]);
            }
            if (gre[pos - 1][area - h[pos]] < INT_MAX) {
               r = min(r, gre[pos - 1][area - h[pos]] + min(h[pos], h[pos - 1]));
            }
         }
         // upd gre[pos][area]
         int &g = gre[pos][area];
         if (red[pos - 1][area] < INT_MAX) {
            g = min(g, red[pos - 1][area] + min(h[pos], h[pos - 1]));
         }
         if (gre[pos - 1][area] < INT_MAX) {
            g = min(g, gre[pos - 1][area]);
         }
      }
   }
   int res = INT_MAX;
   for (int area = 0; area <= a; ++area) {
      if (sm - area >= 0 && sm - area <= b) {
         res = min({res, red[n - 1][area], gre[n - 1][area]});
      }
   }
   cout << (res == INT_MAX ? -1 : res) << '\n';
}

signed main() {
  IOS; PREC;
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  preproc();

  int tc = 1;
  // cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
