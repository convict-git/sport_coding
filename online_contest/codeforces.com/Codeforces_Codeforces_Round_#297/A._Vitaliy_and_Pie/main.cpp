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
   // n rooms
   // requirements
   vector <int> occ(26);
   int N;
   cin >> N;
   string s;
   cin >> s;
   int res = 0;
   for (int i = 0; i < 2*N - 2; i += 2) {
      ++occ[s[i] - 'a']; // add the key you have
      if (occ[s[i + 1] - 'A'] == 0) {
         ++res;
      }
      else {
         --occ[s[i + 1] - 'A'];
      }
   }
   cout << res << '\n';
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
