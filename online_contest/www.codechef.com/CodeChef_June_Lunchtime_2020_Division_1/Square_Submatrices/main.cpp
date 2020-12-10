#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#define ms(x,y,n) for(int i = 0; i < n; ++i) x[i] = y;
typedef long long ll;
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

void preproc() {
}

void solve() {
   int X, N;
   cin >> N >> X;
   vector <int> ar(N);
   vector <ll> pref(N);
   for (int i = 0; i < N; ++i) {
      cin >> ar[i];
      pref[i] = 1ll*ar[i] + (i ? pref[i - 1] : 0ll);
   }
   auto get = [&] (int i, int len) -> ll {
      return pref[i + len - 1] - (i ? pref[i - 1] : 0ll);
   };
   debug(pref);

   // find possible lengths to look for
   vector <int> kpos;
   for (int d = 1; d * d <= X; ++d) {
      if (X % d == 0) {
         kpos.push_back(d);
         if (d != X / d) kpos.push_back(X/d);
      }
   }
   sort(kpos.begin(), kpos.end());
   debug(kpos);

   ll res = 0;
   for (int len : kpos) {
      if (len > N) {
         break;
      }
      debug(X/len, len);
      map <ll, int> mp;
      for (int i = 0; i + len < N; ++i) {
         for (int j = 0; j + len < N; ++j) {
            ll cur = 1ll * len * (get(i, len) + get(j, len));
            if (cur == X) {
               ++res;
            }
         }
      }
      /*
      for (int i = 0; i + len < N; ++i) {
         ll sm = get(i, len);
         ++mp[sm];
      }

      for (int i = 0; i + len < N; ++i) {
         ll sm = get(i, len);
         res += mp[X/len - sm];
      }
      */
   }
   cout << res << '\n';
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
