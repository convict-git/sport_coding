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

void solve()
{
   int N;
   cin >> N;
   vector <vector <int>> mat;
   mat.assign(
         N,
         vector <int> (N)
         );

   for (auto &v : mat) {
      for (int &i : v) {
         cin >> i;
      }
   }

   int curMove = 0;
   for (int j = N - 1; j >= 0; --j) {
      curMove += ((mat[0][j] != j + 1) ^ (curMove & 1)) == 1;
   }
   cout << curMove << '\n';
}

signed main()
{
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
