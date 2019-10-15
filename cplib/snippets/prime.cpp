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
   if (n != 1) pd.push_back(n);
   return td;
}

vector <vector <int>> divisors(int n) {
   vector <vector <int>> div(n, vector <int>());
   vector <vector <pair<int,int>>> p_div(n, vector <pair<int,int>> ());

   for (int i = 2; i < n; ++i) {
      int m = i;
      for (int p : primes){
         if (p * p > i) break;
         int alpha = 0;
         while (m % p == 0) m /= p, ++alpha;
         p_div[i].push_back(make_pair(p, alpha));
      }
      if (m != 1) {
         p_div[i].push_back(make_pair(m, 1));
      }
   }

   for (int i = 2; i < n; ++i) {
      div[i].push_back(1);
      for (auto pp: p_div[i]) {
         int p = pp.first, alpha = pp.second;
         int sz = (int)div[i].size();

         vector <int> p_table{1};
         for (int j = 1; j <= alpha; ++j) {
            p_table.push_back(p_table.back() * p);
         }

         for (int j = 1; j <= alpha; ++j) {
            for (int idx = 0; idx < sz; ++idx) {
               div[i].push_back(div[i][idx] * p_table[j]);
            }
         }
      }
   }
   /*
   for (int i = 2; i < n; ++i) {
      cout << "i : " << i << '\n';
      for (int d : div[i]) cout << d << ' ';
      cout << '\n';
   }
   */
   return div;
}

