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
   vector <int> Ar(N);

   for (int &a : Ar)  cin >> a;
   sort(Ar.begin(), Ar.end());
   int mxElement = *max_element(Ar.begin(), Ar.end());

   int mexA = -1, mexB = -1;
   for (int mex = 0; mex <= mxElement; ++mex) {
      if (Ar[i] == mex) {
         mexA = mex;
      }
      else {
         mexA =
      }
   }
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
