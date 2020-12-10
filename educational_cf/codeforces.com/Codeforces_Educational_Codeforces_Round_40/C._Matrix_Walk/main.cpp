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
   for_each(ar.begin(), ar.end(), [&] (int &p) { cin >> p; });

   int maxAi = *max_element(ar.begin(), ar.end());
   if (N == 1) {
      cout << "YES\n";
      cout << 1 << ' ' << ar[0] << '\n';
      return;
   }

   set <int> s;
   for (int i = 1; i < N; ++i) {
      s.insert(abs(ar[i] - ar[i - 1]));
   }
   debug(s);

   int diff = static_cast <int> (s.size());
   if (diff > 2 or (diff == 2 and *s.begin() != 1) or *s.begin() == 0) {
      cout << "NO\n";
      return;
   }

   cout << "YES\n";

   int Y = 0;
   if (diff == 2) {
      s.erase(s.begin());
      Y = *s.begin();
   }
   else {
      Y = *s.begin();
   }

   int X = (maxAi / Y) + 2;

   cout << X << " " << Y << '\n';
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
