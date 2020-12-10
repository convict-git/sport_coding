#include <bits/stdc++.h>
using namespace std;
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
   cout << primes.size() << '\n';
}

const int N = (int)1e6 + 10;
vector <pair <int, int> > facc[N];
signed main() {
  sieve();
  /*
  for (int i = 2; i < N; ++i) {
    cout << "Factors for i : " << i << " : ";
    for (auto el : facc[i]) {
      cout << "(" << el.first << ", " << el.second << ") ,";
    }
    cout << '\n';
  }
  */
  return EXIT_SUCCESS;
}


