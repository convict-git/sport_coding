#include <bits/stdc++.h>
using namespace std;
#warning 1 based indexing

template <typename T = int>
class FT {
  public:
    size_t n;
    vector <T> bit;

    FT (const vector <T> &v) {
      n = v.size();
      bit.assign(n + 1, 0);
      for (int i = 0; i < n; ++i)
        add(i + 1, n, v[i]);
    }

    inline void add (int x, T val) {
      while (x <= n) bit[x] += val, x += (x & (-x));
    }

    inline T get (int x) {
      int res = 0;
      while (x > 0) res += bit[x], x -= (x & (-x));
      return res;
    }
};
