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

#define x first
#define y second
void solve() {
   int n;
   cin >> n;
   vector <pair <int, int>> range(n);
   for (int i = 0; i < n; ++i) {
      cin >> range[i].x >> range[i].y;
   }
   sort(range.begin(), range.end(), [&] (auto p1, auto p2)
         { return p1.x < p2.x or (p1.x == p2.x and p1.y > p2.y); });

   vector <pair <int, int>> finRange; // merged ranges
   int L=0, R=-1;
   for (int i = 0; i < n; ++i) {
      if (range[i].x >= L and range[i].y <= R) {
         continue;
      }
      else {
         L = range[i].x, R = range[i].y;
         finRange.push_back({L, R});
      }
   }
   int sz=(int)finRange.size();
   // now each range is disjoint on L
   int q, m;
   cin >> q;
   while (q--) {
      cin >> m;
      vector <int> qry(m);
      for (int i = 0; i < m; ++i) {
         cin >> qry[i];
      }

      sort(qry.begin(), qry.end());
      qry.erase(unique(qry.begin(), qry.end()), qry.end());
      int qsz = (int)qry.size();

      // least range that occupies d0
      L = 0, R = -1;
      int res = 0;
      bool ok = true;
      for (int i = 0; i < qsz; ++i) {
         int di = qry[i], l = 0, h = sz-1;
         while (l <= h) {
            int g = (l+h)/2;
            if (finRange[g].x <= di)
               l = g+1;
            else h = g-1;
         }
         if (h == -1 or finRange[h].y < di) {
            ok = false;
            break;
         }
         int X = finRange[h].x, Y = finRange[h].y;
         if (L <= di and di <= R) {
            continue;
         }
         else {
            res += 1;
            L = X, R = Y;
         }
      }
      cout << (ok ? res : -1) << '\n';
   }
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  // cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
