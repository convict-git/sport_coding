const int Mod = (int)1e9 + 7;
// const int Mod = 998244353;
#warning is it 998244353?
#warning call_init_fac
#define M(x) ((int)((x) % Mod))

inline int add (int x, int y) { return M(1ll*M(x) + M(y) + (Mod << 1)); }
inline int sub (int x, int y) { return M(1ll*M(x) - M(y) + (Mod << 1)); }
inline int mul (int x, int y) { return (int) M(1ll*(M(x) + Mod) * (M(y) + Mod)); }
inline int pw (int x, long long y) {
   int res = 1;
   while (y) {
      if (y & 1ll) res = mul(res, x);
      x = mul(x, x), y >>= 1ll;
   }
   return res;
}
inline int inv (int x) { return pw(x, Mod - 2); }
inline int dv (int x, int y) { return mul(x, inv(y)); }

const int MAXFAC = (int)2e6 + 10;
int fac[MAXFAC];
void init_fac (int maxn = MAXFAC) {
   fac[0] = 1;
   for (int i = 1; i < maxn; ++i) fac[i] = mul(fac[i - 1], i);
}
inline int nCr(int n, int r) {
   return dv(fac[n], mul(fac[n-r], fac[r]));
}
