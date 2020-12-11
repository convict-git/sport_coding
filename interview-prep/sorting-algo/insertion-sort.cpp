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

/* insertion sort (worse case is O(N * N) but found good
 * for practical purposes)
 * This is an online algorithm can sort an live stream of numbers
 * coming
 * */
void solve()
{
   int N;
   cin >> N;
   vector <int> Ar;
   while (N--) {
      int el; cin >> el;
      Ar.push_back(el);
      for (int i = (int)Ar.size() - 2; i >= 0; --i) {
         if (Ar[i + 1] < Ar[i]) {
            swap(Ar[i + 1], Ar[i]);
         }
      }
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

