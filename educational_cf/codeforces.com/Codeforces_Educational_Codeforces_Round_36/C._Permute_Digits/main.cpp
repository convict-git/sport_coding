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
   string a, b;
   cin >> a >> b;
   vector <int> cnt(10);
   int beg = (int)b.size() - (int)a.size();
   while (a.size() != b.size()) a = '0' + a;

   for (char ch : a) {
      ++cnt[ch - '0'];
   }
   long long res = 0;
   bool ok = false;
   function <void(int, long long, long long)> dfs =
      [&] (int pos, long long d, long long bb) {
      bb = bb * 10 + (b[pos] - '0');
      if (pos == (int)b.size()) {
         res = max(res, d);
         ok = true;
         return;
      }
      for (int cur = 9; cur >= 0; --cur) {
         long long nw = d*10 + cur;
         if (!ok && cnt[cur] > 0 && nw <= bb) {
            --cnt[cur];
            dfs(pos + 1, nw, bb);
            ++cnt[cur];
         }
      }
   };
   long long bb = 0;
   for (int pos = 0; pos < beg; ++pos)  {
      bb = bb * 10 + (b[pos] - '0');
   }
   dfs(beg, 0, bb);
   cout << res << '\n';
}

signed main() {
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
