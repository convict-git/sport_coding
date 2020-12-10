#include <bits/stdc++.h>
using namespace std;
const int MAX_P = 2101000;
vector <int> primes = {2}, powers;
#warning call sieve
void sieve() {
   vector <bool> isPrime(MAX_P + 1, true);
   for (int i = 3; i*2 <= MAX_P; i += 2) {
      int p = 0;
      while (1ll * i*(i + p) <= MAX_P) { isPrime[i*(i + p)] = false, ++p; }
   }
   for (int i = 3; i <= MAX_P; i += 2) {
      if (isPrime[i]) primes.push_back(i);
   }
   // cerr << primes.size() << '\n';
}

int total_divisors(int n) {
   vector <int> pd; // prime divisors of n
   int td = 1; // total divisors of n
   int n_ref = n;
   for (int p : primes) {
      if (1ll*p*p > 1ll*n_ref) break;
      int alpha = 0;
      if (n % p == 0) pd.push_back(p);
      while (n%p == 0) n/=p, ++alpha;
      td *= (1 + alpha);
      powers.push_back(alpha);
   }
   td *= (1 + (n != 1));
   if (n != 1) pd.push_back(n), powers.push_back(1);
   assert(pd.size() == powers.size());
   return td;
}

int main() {

}
