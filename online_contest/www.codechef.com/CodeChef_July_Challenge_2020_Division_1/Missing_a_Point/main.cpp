#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#define ms(x,y,n) for(int i = 0; i < n; ++i) x[i] = y;
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

void preproc() {
}

void solve() {
   int N;
   cin >> N;
   N *= 4;
   map <int, int> xCntMap, yCntMap;
   set <int> xCor, yCor;

   for (int i = 0; i < N-1; ++i) {
      int x, y;
      cin >> x >> y;
      ++xCntMap[x], ++yCntMap[y];
      xCor.insert(x), yCor.insert(y);
   }
   int resX = -1, resY = -1;
   for (int x : xCor) {
      if (xCntMap[x] % 2 == 1) {
         resX = x;
         break;
      }
   }
   for (int y : yCor) {
      if (yCntMap[y] % 2 == 1) {
         resY = y;
         break;
      }
   }
   cout << resX << ' ' << resY << '\n';
}

signed main() {
  IOS; PREC;
  preproc();
  int tc = 1;
  cin >> tc;

  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
