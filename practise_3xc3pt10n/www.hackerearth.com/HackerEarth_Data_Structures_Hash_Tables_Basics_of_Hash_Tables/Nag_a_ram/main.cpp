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
   string s;
   vector <pair <int, string>> store;
   auto find_group = [&] (const string &st) -> int {
      int x = 0;
      for (char ch : st) {
         x |= (1 << (ch - 'a'));
      }
      return x;
   };
   for (int i = 0; i < N; ++i) {
      cin >> s;
      store.emplace_back(find_group(s), s);
   }

   sort(store.begin(), store.end());
   for (int i = 0; i < N; ++i) {
      cout << store[i].second;
      if ((i + 1 <= N - 1 and store[i + 1].first != store[i].first)
            or i == N - 1)
      {
         cout << '\n';
      }
      else cout << ' ';
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
