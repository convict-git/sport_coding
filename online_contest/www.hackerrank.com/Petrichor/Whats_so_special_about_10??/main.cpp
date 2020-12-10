// Hack it and have it ;) //
/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows!* * * * * * */
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

void preproc() {
}

void solve() {
   int n;
   cin >> n;
   // if (n == 5 || (n == 6 && (n-6) % 2 == 0 && ((n-6)/2) % 2 == 0) || (n > 10 && (n-10) % 2 == 1)) {
   if (n >= 4) {
      cout << "Yes\n";
   }
   else cout << "No\n";
}

signed main() {
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
