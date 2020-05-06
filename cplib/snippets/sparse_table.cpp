#include <bits/stdc++.h>
using namespace std;

#define T(x) (1 << (x))
template <typename __S = int>
class binop {
  public:
    __S operator () (const __S &x, const __S &y) {
      return max(x, y);
    }
};

template <class __F = long long, class __B = binop <__F>>
class sparse_table {
  public:
    static const int D = 21;
    int n;
    vector <vector <__F>> dp, who;
    vector <int> LOG;

    sparse_table (const vector <__F> &v) {
      n = static_cast <int> (v.size());
      dp.assign(D + 1, vector <__F> (n));
      who.assign(D + 1, vector <__F> (n));
      LOG.assign(n + 1, 0);

      for (int i = 0; i < n; ++i)
        dp[0][i] = v[i];
      iota(who[0].begin(), who[0].end(), 0);

      for (int k = 1; k <= D; ++k)
        for (int i = 0; i < n; ++i)
          if (i + T(k) - 1 < n) {
            __F lt = dp[k - 1][i], rt = dp[k - 1][i + T(k - 1)];
            if (__B() (lt, rt) == lt) { // max or min
              who[k][i] = who[k - 1][i];
              dp[k][i] = lt;
            }
            else {
              who[k][i] = who[k - 1][i + T(k - 1)];
              dp[k][i] = rt;
            }
          }

      for (int i = 2; i <= n; ++i)
        LOG[i] = LOG[i / 2] + 1;
    }

    pair <__F, int> get (int l, int r) {
      int k = LOG[r - l + 1];
      __F lt = dp[k][l], rt = dp[k][r - T(k) + 1];
      return (__B () (lt, rt) == lt ? make_pair(who[k][l], lt) : make_pair(who[k][r - T(k) + 1], rt)); // max or min
    }

    pair <int, int> get_range (int idx) {
      int L = idx, R = idx;
      for (int k = D; k >= 0; --k)
        if (R + T(k) - 1 < n && dp[k][R] >= dp[0][idx])
          R += T(k);
      --R;
      for (int k = D; k >= 0; --k)
        if (L - T(k) + 1 >= 0 && dp[k][L - T(k) + 1] >= dp[0][idx])
          L -= T(k);
      ++L;
      return make_pair(L, R);
    }
};
#undef T

// sparse_table <int> ST(v); // or sparse_table ST(v); // or sparse_table <long long> ST(v);
