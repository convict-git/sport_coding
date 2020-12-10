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
   int N, T;
   cin >> N >> T;
   struct Tap {
      int temp, maxAllowed;
      bool operator < (const Tap &t) const {
         return temp < t.temp;
      }
   };
   vector <Tap> tapsInfo(N);
   vector <long double> finalValues(N);

   long double finalTemp = 0;

   for (int i = 0; i < N; ++i) {
      cin >> tapsInfo[i].maxAllowed;
   }
   for (int i = 0; i < N; ++i) {
      cin >> tapsInfo[i].temp;
      tapsInfo[i].temp -= T; // store t' instead of t, defined as t' = t - T

      finalTemp += static_cast<long double>
         (tapsInfo[i].maxAllowed) * tapsInfo[i].temp;
   }

   sort(tapsInfo.begin(), tapsInfo.end());
   for (int i = 0; i < N; ++i){
      finalValues[i] = static_cast <long double> (tapsInfo[i].maxAllowed);
   }

   const long double eps = 1e-9;

   int leftPtr = 0, rightPtr = N - 1;

   while (fabs(finalTemp) > eps) {
      long double canGetMax;
      if (finalTemp > 0) {
         if (rightPtr < 0 or tapsInfo[rightPtr].temp < 0) {
            cout << 0 << '\n';
            return;
         }
         canGetMax = static_cast <long double>
            (tapsInfo[rightPtr].maxAllowed) * tapsInfo[rightPtr].temp;

         if (finalTemp - canGetMax < eps) {
            finalValues[rightPtr] -= finalTemp / tapsInfo[rightPtr].temp;
            finalTemp = 0.0;
         }
         else {
            finalValues[rightPtr] = 0;
            finalTemp -= canGetMax;
         }
         --rightPtr;
      }
      else {
         if (leftPtr > N - 1 or tapsInfo[leftPtr].temp > 0) {
            cout << 0 << '\n';
            return;
         }
         canGetMax = static_cast <long double>
            (tapsInfo[leftPtr].maxAllowed) * tapsInfo[leftPtr].temp;

         if (canGetMax - finalTemp < eps) {
            finalValues[leftPtr] -= finalTemp / tapsInfo[leftPtr].temp;
            finalTemp = 0.0;
         }
         else {
            finalValues[leftPtr] = 0;
            finalTemp -= canGetMax;
         }
         ++leftPtr;
      }
   }
   long double res = 0.0;
   for (int i = 0; i < N; ++i) {
      res += finalValues[i];
   }
   cout << res << '\n';
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
