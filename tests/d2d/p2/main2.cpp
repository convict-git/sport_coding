#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int n;
  cin >> n;
  int cr = (int)1e7;
  vector <int> ar(n + 1);
  vector <long long> pref(n + 1), suff(n + 2);
  for (int i = 1; i <= n; ++i)
    cin >> ar[i];
  sort(ar.begin(), ar.end());
  for (int i = 1; i <= n; ++i)
    pref[i] = pref[i - 1] + ar[i];
  for (int i = n; i >= 1; --i)
    suff[i] = suff[i + 1] + ar[i];

  set <int> s;
  auto fn = [&] (const int &x) -> bool {
    return s.find(x) != s.end();
  };

  if (pref[n] < cr) {
    cout << -1 << '\n';
  }
  else {
    long long nt = 0;
    long long sm = 0;
    int res = 0;
    for (int i = 1; i <= n; ++i) {
      if (sm >= cr) {
        break;
      }

      if (fn(ar[i]) && pref[i - 1] - nt + suff[i + 1] >= cr) {
        nt += ar[i];
        continue;
      }
      s.insert(ar[i]);
      sm += ar[i];
      ++res;
    }
    cout << res << '\n';
  }

    return 0;
}
