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

const int Mod = (int)1e9 + 7;
// const int Mod = 998244353;
#warning is it 998244353?
#define M(x) ((int)((x) % Mod))

inline int add (int x, int y) { return M(1ll*M(x) + M(y) + (Mod << 1)); }
inline int sub (int x, int y) { return M(1ll*M(x) - M(y) + (Mod << 1)); }
inline int mul (int x, int y) { return (int) M(1ll*(M(x) + Mod) * (M(y) + Mod)); }
inline int pow (int x, long long y) {
  int res = 1;
  while (y) {
    if (y & 1ll) res = mul(res, x);
    x = mul(x, x), y >>= 1ll;
  }
  return res;
}
inline int inv (int x) { return pow(x, 1ll*Mod - 2); }
inline int dv (int x, int y) { return mul(x, inv(y)); }

const int MAXFAC = (int)2e6 + 10;
int fac[MAXFAC];
#warning call_init_fac
void init_fac (int maxn) {
  fac[0] = 1;
  for (int i = 1; i < maxn; ++i) fac[i] = mul(fac[i - 1], i);
}
inline int C(int n, int r) {
  return dv(fac[n], mul(fac[n-r], fac[r]));
}
void preproc()
{
   init_fac(MAXFAC);
}

void solve()
{
   int H, W, A, B;
   cin >> H >> W >> A >> B;

   int res = 0;
   // part I -> height -> H - A, width -> i
   // part II -> height -> A, width -> W - i + 1
   for (int i = B+1; i <= W; ++i) {
      int inc = mul(C(H - A + i - 2, i - 1), C(A + W - i - 1, A - 1));
      res = add(res, inc);
   }
   cout << res << '\n';
}

signed main()
{
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
