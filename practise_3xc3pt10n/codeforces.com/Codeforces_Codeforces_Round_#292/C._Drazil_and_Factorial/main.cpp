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
   vector <string> mp
   {"#", "*", "2", "3", "322", "5", "35", "7", "7222", "7332"};

   int N;
   long long X;
   cin >> N >> X;

   string res = "";
   while (X) {
      int curDigit = X % 10;
      if (curDigit >= 2) res.append(mp[curDigit]);
      X /= 10;
   }
   sort(res.begin(), res.end());
   reverse(res.begin(), res.end());
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
