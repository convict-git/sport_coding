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

inline int add (int x, int y) {
   return x == INT_MAX ? INT_MAX : x + y;
}

void solve()
{
   int a, b;
   string s;
   cin >> a >> b >> s;
   s.push_back('#');
   int N = (int)s.size(); // one more than actual N
   vector <pair <int, int>> ar;
   int idx = 0;
   while (idx < N-1) {
      int zero = 0, one = 0;
      while (idx < N and s[idx] == '0') {
         ++zero;
         ++idx;
      }
      while (idx < N and s[idx] == '1') {
         ++one;
         ++idx;
      }
      if (zero) ar.push_back(make_pair(zero, 0));
      if (one) ar.push_back(make_pair(one, 1));
   }

   int sz = (int)ar.size();
   vector <int> one(sz, INT_MAX);
   vector <int> zero(sz, INT_MAX);

   one[0] = ar[0].second ? a : b * ar[0].first + a;
   zero[0] = ar[0].second ? INT_MAX : 0;

   for (int pos = 1; pos < sz; ++pos) {
      if (ar[pos].second) {
         zero[pos] = INT_MAX;
         one[pos] = min(add(zero[pos - 1], a), one[pos - 1]);
      } else {
         zero[pos] = min(zero[pos - 1], one[pos - 1]);
         one[pos] = min(add(zero[pos - 1], b * ar[pos].first + a), add(one[pos - 1], b * ar[pos].first));
      }
   }
   cout << min(one[sz - 1], zero[sz - 1]) << endl;
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
