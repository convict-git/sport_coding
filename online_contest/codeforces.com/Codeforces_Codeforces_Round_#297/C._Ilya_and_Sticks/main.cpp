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
   vector <int> ar(N);
   for (int i = 0; i < N; ++i) {
      cin >> ar[i];
   }
   vector <int> sides;
   sort(ar.begin(), ar.end(), greater <int> ());

   for (int i = 0; i < N; ++i) {
      if (i + 1 <= N - 1 and
            ar[i] == ar[i + 1]) {
         sides.push_back(ar[i]);
         i += 1;
      }
      else if (i + 1 <= N - 1 and
            ar[i] == ar[i + 1] + 1) { // use the instrument
         --ar[i];
         sides.push_back(ar[i + 1]);
         i += 1;
      }
      else { // you leave
      }
   }

   long long res = 0;
   // sides in sorted order in decreasing order
   int M = (int)sides.size();
   for (int i = 0; i < M; i += 2) {
      if (i + 1 <= M - 1)
         res += 1ll * sides[i] * sides[i + 1];
   }
   cout << res << '\n';
   return;

   // lenghts are sorted
   // 5 4 4 3 2 1 1
   // 1 1 2 2 3 4 4 5
   // 1 1 2 2         3 3              4 4
   //
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
