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

/*
 * Bubble sort :  O(N * N) worse case, O(N) best case
 * Can detect whether already sorted with a flag and work in O(N)
 * But generally not recommended to use, only when you know it's
 * almost sorted then it's fine
 */
void solve()
{
   int N;
   cin >> N;
   vector <int> Ar(N);
   for (int &a : Ar) cin >> a;

   // will take atmost N - 1 passes. Think why?
   // (hint: smallest element  is in the last position)
   for (int pass = 1; pass <= N - 1; ++pass) {
      bool swapNeeded = false;
      for (int i = 0; i < N - 1; ++i) {
         if (Ar[i + 1] < Ar[i]) {
            swapNeeded = true;
            swap(Ar[i + 1], Ar[i]);
         }
      }
      if (!swapNeeded) break;
   }
   for (int &a : Ar) cout << a << ' ';
   cout << '\n';
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

