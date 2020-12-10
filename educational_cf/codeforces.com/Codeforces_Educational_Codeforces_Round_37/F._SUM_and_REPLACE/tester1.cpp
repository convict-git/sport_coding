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

const int MAX_P = 2101000;
vector <int> primes = {2}, powers;
void sieve() {
   vector <bool> isPrime(MAX_P + 1, true);
   for (int i = 3; i*2 <= MAX_P; i += 2) {
      int p = 0;
      while (1ll * i*(i + p) <= MAX_P) isPrime[i*(i + p)] = false, ++p;
   }
   for (int i = 3; i <= MAX_P; i += 2) {
      if (isPrime[i]) primes.push_back(i);
   }
   // cerr << primes.size() << '\n';
}

inline int total_divisors(int n) {
   int td = 1; // total divisors of n
   int n_ref = n;
   for (int p : primes) {
      if (1ll*p*p > 1ll*n_ref) break;
      int alpha = 0;
      while (n%p == 0) n/=p, ++alpha;
      td *= (1 + alpha);
      if (n_ref == 100){
         debug(td, 1+alpha, p);
      }
   }
   td *= (1 + (n != 1));
   return td;
}

const int mxn = 1e6;
vector <int> dv(mxn+1);
vector <int> impdv(mxn+1);

void preproc() {
   for (int i = 1; i <= mxn; ++i) {
      dv[i] = total_divisors(i);
      for (int j = 0; j <= mxn; j += i) {
         ++impdv[j];
      }
   }
   debug(dv[100], impdv[100]);
}

void solve() {
   int n, m;
   cin >> n >> m;
   vector <int> ar(n);
   for (int i = 0; i < n; ++i){
      cin >> ar[i];
   }
   while (m--) {
      int k, l, r;
      cin >> k >> l >> r;
      --l, --r;
      if (k == 2) {
         long long res = 0;
         for (int i = l; i <= r; ++i) {
            res += ar[i];
         }
         cout << res << '\n';
      }
      else {
         for (int i = l; i <= r; ++i) {
            ar[i] = dv[ar[i]];
         }
      }
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
