#warning for N = 1e6, N * logN * logN is approx 4e8 (so it may timeout)
#warning p[Log][i] corresponding to the string "$", and n is len of (original string + "$")
#warning Compiler optimization doesn't work good with this
#include <bits/stdc++.h>
using namespace std;

struct suffix_array {
  const int Log = 20;

  string s;
  vector <vector <int>> p, c;
  vector <int> lp, sa;
  int n;

  void cyclic_sort () { // O(|s| * (log|s|)^2)
    iota(p[0].begin(), p[0].end(), 0);
    sort (p[0].begin(), p[0].end(), [&] (const int &x, const int &y) -> bool {
        return s[x] < s[y];
        });

    int ck = 0;
    c[0][p[0][0]] = ck;
    for (int i = 1; i < n; ++i)
      c[0][p[0][i]] = ck += (s[p[0][i]] != s[p[0][i - 1]]);

    for (int k = 1; k <= Log; ++k) {
      int pw = 1 << (k - 1);
      iota(p[k].begin(), p[k].end(), 0);

      sort (p[k].begin(), p[k].end(), [&] (const int &x, const int &y) -> bool {
          return c[k - 1][x] < c[k - 1][y] ||
          (c[k - 1][x] == c[k - 1][y] &&
           c[k - 1][(x + pw) % n] < c[k - 1][(y + pw) % n]);
          });

      c[k][p[k][0]] = ck = 0;
      for (int i = 1; i < n; ++i)
        c[k][p[k][i]] =
          ck += (c[k - 1][p[k][i]] != c[k - 1][p[k][i - 1]]
              || c[k - 1][(p[k][i] + pw) % n] != c[k - 1][(p[k][i - 1] + pw) % n]);
    }
  }

  int lcp(int i, int j) { // in cyclic string (NOTE, otherwise change starting value of k)
    int res = 0;
    for (int k = Log; k >= 0; --k) {
      if (i + (1 << k) - 1 > n || j + (1 << k) - 1 > n) continue; // to remove the cyclic constraint
      if (c[k][i] == c[k][j])
        i += (1 << k), j += (1 << k), res += (1 << k);
    }
    return res;
  }

  suffix_array (string s_) {
    s = s_ + "$";
    n = (int)s.size();
    p.assign(Log + 1, vector <int> (n));
    c.assign(Log + 1, vector <int> (n));
    sa.assign(n + 1, 0);
    lp.assign(n + 1, 0);

    cyclic_sort();
    for (int i = 0; i < n; ++i) {
      sa[i] = p[Log][i];
      if (i != n - 1) lp[i] = lcp(p[Log][i], p[Log][i + 1]);
    }
  }

  int compare (int i, int j, int k, int len) { // O(1)
    pair <int, int> s1 = make_pair(c[k][i], c[k][(i + len - (1 << k)) % n]);
    pair <int, int> s2 = make_pair(c[k][j], c[k][(j + len - (1 << k)) % n]);
    return s1 == s2 ? 0 : s1 < s2 ? -1 : 1;
  }

  friend ostream& operator << (ostream &os, const suffix_array &S) {
    for (int i = 0; i < S.n; ++i) {
      os << S.s.substr(i, S.n - i) << '\n';
    }
    return os;
  }
};
