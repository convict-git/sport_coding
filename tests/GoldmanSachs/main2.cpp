#include      <bits/stdc++.h>
using namespace std;
#pragma GCC   optimize ("Ofast")
#pragma GCC   optimize ("unroll-loops")
#pragma GCC   target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS   ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC  cout.precision (10); cout << fixed
#define x     first
#define y     second
#define bg(x) " [ " << #x << " : " << (x) << " ] "
#define un(x) sort(x.begin(), x.end()), \
              x.erase(unique(x.begin(), x.end()), x.end())
using   ll  = long long;
using   ff  = long double;
using   pii = pair<int,int>;
using   pil = pair<int,ll>;
/*****************************************************************************/

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
}

int sumOfprimes(int n) {
   vector <int> pd;
   int n_ref = n;
   for (int p : primes) {
      if (1ll*p*p > 1ll*n_ref) break;
      int alpha = 0;
      if (n % p == 0) pd.push_back(p);
      while (n%p == 0) n/=p, ++alpha;
      powers.push_back(alpha);
   }
   if (n != 1) pd.push_back(n);
   int ans = 0;
   for (int el : pd) {
      ans += el;
      ans %= ((int)1e6);
   }
   return ans;
}

const int Mod = (int)1e9 + 7;

int mul (int a, int b) {
   return int(1ll*a*b % Mod);
}

int add (int a, int b) {
   return (a + b) % Mod;
}

int expo (int a, int x) {
   int res = 1;
   while (x){
      if (x & 1) res = mul(res, a);
      a = mul(a, a);
      x >>= 1;
   }
   return res;
};

int getSubsets(int k, int n, vector<int> arr) {
   sieve();
   int primeSum = 0;
   for (int i = 0; i < (int)arr.size(); ++i) {
      primeSum += sumOfprimes(arr[i]);
      primeSum %= ((int)1e6);
   }
   int num = 1, den = 1;
   for (int i = 1; i <= primeSum + k - 1; ++i) {
      num = mul(num, i);
   }
   for (int i = 1; i <= k - 1; ++i) {
      den = mul(den, i);
   }
   for (int i = 1; i <= primeSum; ++i) {
      den = mul(den, i);
   }
   den = expo(den, Mod - 2);
   int ans = mul(num, den);
   return ans;
}

signed main() {
   IOS; PREC;
   vector <int> ar;
   int k, n;
   cin >> k >> n >> n;
   ar.assign(n, 0);
   for (int i = 0; i < n; ++i) {
      cin >> ar[i];
   }
   cout << getSubsets(k, n, ar) << '\n';

   return EXIT_SUCCESS;
}

