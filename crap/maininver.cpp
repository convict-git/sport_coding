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

const int N = (int)1e6 + 10;
int bit[N];
int n;
long long ar[N];
vector <long long> v;

inline void upd(int x, int val) {
  while (x <= n) bit[x] += val, x += (x & -x);
}

inline int sum (int x) {
  int res = 0;
  while (x > 0) res += bit[x], x -= (x & -x);
  return res;
}

inline int idx (long long x) {
  return int (upper_bound(v.begin(), v.end(), x) - v.begin()) + 1;
}

signed main() {
  IOS; PREC;
  int tc;
  cin >> tc;
  while (tc--) {
    cin >> n;
    v.assign(n, 0);
    for (int i = 0; i < n; ++i)
      cin >> ar[i], v[i] = ar[i];
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    long long res = 0;
    for (int i = n - 1; i >= 0; --i) {
      res += sum(idx(ar[i]) - 1);
      upd(idx(ar[i]), 1);
    }
    cout << res << '\n';
  }
  return EXIT_SUCCESS;
}
