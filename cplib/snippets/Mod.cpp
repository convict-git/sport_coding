const int Mod = (int)1e9 + 7;
inline int add (int x, int y) { return (x + y) % Mod; }
inline int sub (int x, int y) { return (x - y + Mod) % Mod; }
inline int mul (int x, int y) { return (int) (1ll*x*y % Mod); }
inline int pow (int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) res = mul(res, x);
    x = mul(x, x), y >>= 1;
  }
  return res;
}
inline int inv (int x) { return pow(x, Mod - 2); }
inline int dv (int x, int y) { return mul(x, inv(y)); }

const int MAXFAC = (int)1e6 + 10;
int fac[MAXFAC];
void init_fac (int maxn) {
#WARNING call_init_fac
  fac[0] = 1;
  for (int i = 1; i < maxn; ++i) fac[i] = mul(fac[i - 1], i);
}
inline int C(int n, int r) {
  return dv(fac[n], mul(fac[n-r], fac[r]));
}
