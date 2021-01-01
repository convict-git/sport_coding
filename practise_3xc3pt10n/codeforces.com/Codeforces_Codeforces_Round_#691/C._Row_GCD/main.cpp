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
typedef long long Int;

void preproc()
{
#warning No preprocessing done
}

void reset()
{
#warning No resetting of global variables done
}

void solve()
{
   int N, M;
   cin >> N >> M;
   vector <Int> a(N);
   for (Int &x: a) cin >> x;
   sort(a.begin(), a.end());
   vector <Int> b(M);
   for (Int &x: b) cin >> x;

   if (N == 1) {
      for (Int x : b) cout << a[0] + x << ' ';
      cout << '\n';
      return;
   }

   Int gcdAc = a[1] - a[0];
   for (int i = 2; i < N; ++i) {
      gcdAc = __gcd(gcdAc, a[i] - a[i - 1]);
   }
   for (Int x : b) cout << __gcd(a[0] + x, gcdAc) << ' ';
   cout << '\n';
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
      reset();
      solve();
   }
   return EXIT_SUCCESS;
}
