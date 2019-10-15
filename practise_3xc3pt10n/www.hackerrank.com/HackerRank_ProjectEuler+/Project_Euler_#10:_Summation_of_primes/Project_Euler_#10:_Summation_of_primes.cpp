#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ]"
#define x        first
#define y        second

#define debug(args...) { \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) { it->empty();
   cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}
using ll = long long;

const int MAX_P = 17010000;
vector <int> primes = {2};
vector <ll> cum_primes;
void sieve() {
   vector <bool> isPrime(MAX_P + 1, true);
   for (int i = 3; i*2 <= MAX_P; i += 2) {
      int p = 0;
      while (1ll * i*(i + p) <= MAX_P) isPrime[i*(i + p)] = false, ++p;
   }
   for (int i = 3; i <= MAX_P; i += 2) {
      if (isPrime[i]) primes.push_back(i);
   }

   for (int i = 0; i < (int)primes.size(); ++i) {
      if (!i) cum_primes.push_back(primes[i]);
      else cum_primes.push_back(1ll*primes[i] + cum_primes[i - 1]);
   }
}

ll solve(int n) {
   int idx = int(upper_bound(primes.begin(), primes.end(), n) - primes.begin() - 1);
   assert(idx >= 0 && idx < (int)primes.size());
   return cum_primes[idx];
}

signed main() {
   IOS; PREC;
   sieve();
   int tc; cin >> tc;
   while (tc--) {
      int n; cin >> n;
      cout << solve(n) << '\n';
   }


   return EXIT_SUCCESS;
}

