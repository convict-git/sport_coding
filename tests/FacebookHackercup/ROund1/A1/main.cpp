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
inline int add (int x, int y) { return (1ll * x + y + (Mod << 1)) % Mod; }
inline int sub (int x, int y) { return (1ll * x - y + (Mod << 1)) % Mod; }
inline int mul (int x, int y) { return (int) (1ll*(x + Mod) * (y + Mod) % Mod); }
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

void preproc()
{
}

void solve()
{
   int N, K, W;
   cin >> N >> K >> W;
   vector <int> L(N), H(N);
   for_each(L.begin(), L.begin() + K, [&] (int &p) { cin >> p; });
   vector <int> parL(4), parH(4);
   for_each(parL.begin(), parL.end(), [&] (int &p) { cin >> p; });
   for_each(H.begin(), H.begin() + K, [&] (int &p) { cin >> p; });
   for_each(parH.begin(), parH.end(), [&] (int &p) { cin >> p; });

   auto giveVal = [&] (int A, int B, int C, int D, int prev, int pprev) -> int {
      return int(((1ll*A*pprev % D) + (1ll*B*prev % D) + C % D) % D) + 1;
   };

   int res = 1;
   for (int i = K; i < N; ++i) {
      L[i] = giveVal(parL[0], parL[1], parL[2], parL[3], L[i - 1], L[i - 2]);
   }
   for (int i = K; i < N; ++i) {
      H[i] = giveVal(parH[0], parH[1], parH[2], parH[3], H[i - 1], H[i - 2]);
   }

   for (int i = 0; i < N; ++i) {
      int Pi = 2*add(W, H[i]);
      if (i != 0 and L[i - 1] + W > L[i]) {

      }
}

signed main()
{
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
