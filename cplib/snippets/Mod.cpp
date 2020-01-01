const int Mod = 1e9 + 7;
inline int add (int x, int y) { return (x+y) % Mod; }
inline int sub (int x, int y) { return (x-y+Mod) % Mod; }
inline int mul (int x, int y) { return static_cast <int> (1ll*x*y % Mod); }
inline int pow (int x, int y) {
  int res=1;
  while (y) { if (y&1) res=mul(res, x); x=mul(x, x), y>>=1; }
  return res;
}
inline int dv (int x, int y) { return mul(x, pow(y, Mod-2)); }

