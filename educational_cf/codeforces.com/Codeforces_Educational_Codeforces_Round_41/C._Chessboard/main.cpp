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
   vector <vector <string>> mat(4, vector <string> (N));
   for (int rot = 0; rot < 4; ++rot) {
      for (int i = 0; i < N; ++i) {
         cin >> mat[rot][i];
         assert((int)mat[rot][i].size() == N);
      }
   }

   vector <int> pi{0, 1, 2, 3};

   int mn = INT_MAX;
   do { // 4!
      for (char starts : {'0', '1'}) {
         int cur = 0;
         // 2 3 1 0
         for (int rotIdx = 0; rotIdx < 4; ++rotIdx) {
            int rot = pi[rotIdx];
            for (int i = 0; i < N; ++i) {
               for (int j = 0; j < N; ++j) {
                  if ((i + j + rotIdx) % 2 == 0 and  mat[rot][i][j] != starts) {
                     ++cur;
                  }
                  else if ((i + j + rotIdx) % 2 != 0
                        and mat[rot][i][j] == starts) {
                     ++cur;
                  }
               }
            }
         }
         mn = min(cur, mn);
      }
   } while (next_permutation(pi.begin(), pi.end()));
   cout << mn << '\n';
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
