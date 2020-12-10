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
void preproc() {
   sieve();
}

void solve() {
   int n; cin >> n;
   int pw2 = 0;
   int _n = n;
   while (_n % 2 == 0) _n /= 2, pw2++;

   int cnt = 0;
   int __n = _n;
   for (int p : primes) {
      if (p * p > _n) break;
      while (_n % p == 0) _n /= p, ++cnt;
   }

   if (n == 1) {
      cout << "FastestFinger\n";
   }
   else if (n == 2) {
      cout << "Ashishgup\n";
   }
   else if (pw2 == 0) {
      cout << "Ashishgup\n";
   }
   else if (__n != 1 and pw2 != 1) {
      cout << "Ashishgup\n";
   }
   else if (pw2 != 1 and cnt >= 2) {
      cout << "Ashishgup\n";
   }
   else {
      cout << "FastestFinger\n";
   }
   return;
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
