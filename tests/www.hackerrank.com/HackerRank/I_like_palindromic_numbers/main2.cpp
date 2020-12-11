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
   int ev = 0, od = 1;
   int q;
   cin >> q;
   struct co {long long m; int k, n, idx, res = 0;};
   vector <co> qry(q);
   for (int i = 0; i < q; ++i) {
      long long n, m; int k;
      cin >> n >> m >> k;
      qry[i] = {m, k, int((-1ll * (n%k) +k) % k), i, 0};
   }

   vector <vector <int>> cnt(21, vector <int> (21));
   auto upd = [&] (long long M, int &x, auto F) {
      while (F(x) <= M) {
         long long tp = F(x);
         for (int dv = 1; dv <= 20; ++dv) {
            ++cnt[dv][int(tp % dv)];
         }
         ++x;
      }
   };
   auto geteven = [&] (int x) {
      string s = to_string(x), rve = s;
      reverse(rve.begin(), rve.end());
      return stoll(s + rve);
   };
   auto getodd = [&] (int x) {
      string s = to_string(x), rvo = s.substr(0, (int)s.size()-1);
      reverse(rvo.begin(), rvo.end());
      return stoll(s + rvo);
   };

   sort(qry.begin(), qry.end(), [&] (co &x, co &y) {return x.m < y.m;});
   for (int i = 0; i < q; ++i) {
      co &t = qry[i];
      upd(t.m, ev, geteven);
      upd(t.m, od, getodd);
      t.res = cnt[t.k][t.n];
   }
   sort(qry.begin(), qry.end(), [&] (co &x, co &y) {return x.idx < y.idx;});
   for (int i = 0; i < q; ++i) {
      cout << qry[i].res << '\n';
   }
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
