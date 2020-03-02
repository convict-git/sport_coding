#warning /* 1 based indexing */
const int N = (int)2e6 + 10;
int bit[N];

inline void add (int x, int n, int val) {
  while (x <= n) bit[x] += val, x += (x & (-x));
}

inline int get (int x) {
  int res = 0;
  while (x > 0) res += bit[x], x -= (x & (-x));
  return res;
}

