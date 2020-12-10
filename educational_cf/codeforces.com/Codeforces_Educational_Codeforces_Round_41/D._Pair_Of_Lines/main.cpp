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

void preproc()
{
}

struct Point { int x, y; };

inline bool onLine (Point p1, Point p2, Point pts) {
   Point a = {p1.x - pts.x, p1.y - pts.y};
   Point b = {p2.x - pts.x, p2.y - pts.y};
   return 1ll * a.x * b.y - 1ll * a.y * b.x == 0ll;
}

void solve()
{
   int N;
   cin >> N;
   vector <Point> pts(N);
   for (int i = 0; i < N; ++i) {
      cin >> pts[i].x >> pts[i].y;
   }
   if (N <= 2) {
      cout << "YES\n";
      return;
   }

   auto check = [&] (int p1Idx, int p2idx) -> bool {
      Point s = pts[p1Idx], e = pts[p2idx];
      vector <Point> leftOut;
      for (int i = 0; i < (int)pts.size(); ++i) {
         if (i != p1Idx and i != p2idx) {
            if (!onLine(s, e, pts[i])) { leftOut.push_back(pts[i]); }
         }
      }

      if (leftOut.size() <= 2) return true;
      for (int i = 2; i < (int)leftOut.size(); ++i) {
         if (!onLine(leftOut[0], leftOut[1], leftOut[i])) return false;
      }
      return true;
   };

   if (check(0, 1) or check(0, 2) or check(1, 2)) { cout << "YES\n"; }
   else { cout << "NO\n"; }

   return;
}

signed main()
{
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
