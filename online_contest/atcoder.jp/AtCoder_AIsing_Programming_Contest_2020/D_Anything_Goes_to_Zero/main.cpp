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

const int Maxn = 1e6 + 10;
int dp[Maxn];
string X;

void preproc() {
}

int getVal (int Mod) {
   int res = 0, x = 1;
   int sz = (int)X.size();
   for (int i = sz-1; i >= 0; --i) {
      if (X[i] == '1') {
         res = (res + x) % Mod;
      }
      x = x*2 % Mod;
   }
   return res;
}
int pw2Giveny (int y, int Mod) {
   int res = 1, x = 2;
   while (y) {
      if (y & 1) res = 1ll*res*x % Mod;
      x = 1ll*x*x % Mod;
      y >>= 1;
   }
   return res;
}

void solve() {
   int N;
   cin >> N >> X;
   dp[0] = 0;
   for (int i = 1; i <= N; ++i) {
      dp[i] = 1 + dp[i % __builtin_popcount(i)];
   }

   int cntTotal = 0;
   for (char ch : X) cntTotal += (ch == '1');
   int modLow = cntTotal - 1, modHigh = cntTotal + 1;
   int lowVal = getVal(modLow);
   int highVal = getVal(modHigh);

   for (int i = 0; i < N; ++i) {
      int rem, firstStep;
      if (X[i] == '1') {
         if (cntTotal == 1) {
            cout << 0 << '\n';
            continue;
         }
         rem = pw2Giveny(N-i-1, modLow);
         firstStep = (lowVal - rem + modLow) % modLow;
      }
      else {
         rem = pw2Giveny(N-i-1, modHigh);
         firstStep = (highVal + rem) % modHigh;
      }
      cout << 1 + dp[firstStep] << '\n';
   }
}

signed main() {
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
