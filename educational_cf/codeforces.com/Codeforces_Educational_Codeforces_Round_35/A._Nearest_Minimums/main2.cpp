#include         <bits/stdc++.h>
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#define unq(x)    sort(x.begin(), x.end()), x.erase(unique(x.begin(), x.end()), x.end())
using namespace std;
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.cpp"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

void preproc() {
}

void solve() {
  int n;
  cin >> n;
  int mn = INT_MAX, diff = n + 1, lst_idx = -1;
  for (int i = 0, x; i < n; ++i) {
    cin >> x;
    debug(x, mn, diff, lst_idx);
    if (mn > x) {
      mn = x;
      lst_idx = i;
      diff = n + 1;
    }
    else if (x == mn) {
      diff = min(diff, i - lst_idx);
      lst_idx = i;
    }
  }
  cout << diff << '\n';
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

