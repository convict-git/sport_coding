/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows * * * * * * */
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

const int N = (int)1e6;
vector <bool> isPrime;
vector <int> primes;

void sieve() {
   isPrime.assign(N + 1, true);
   for (int i = 2; i <= N/2; ++i) {
      int p = 2;
      while (i * p <= N) isPrime[i * p] = false, ++p;
   }
   for (int i = 2; i <= N; ++i) {
      if (isPrime[i]) primes.push_back(i);
   }
}

ll solve(ll n) {
   int mx_prime = 2;
   ll n_ref = n;
   for (int p : primes) {
      if (1ll * p * p > n_ref) break;
      while (n % p == 0) n /= p, mx_prime = max(mx_prime, p);
   }
   if (n == 1) return mx_prime;
   else return n;
}

signed main() {
   IOS; PREC;
   sieve();

   int tc; cin >> tc;
   long long n;
   while (tc--) {
      cin >> n;
      cout << solve(n) << '\n';
   }

   return EXIT_SUCCESS;
}
