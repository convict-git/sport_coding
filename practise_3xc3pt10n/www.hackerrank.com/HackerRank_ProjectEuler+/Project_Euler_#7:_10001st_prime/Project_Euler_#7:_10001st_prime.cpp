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

const int N = 110100;
vector <int> primes = {2};
void sieve() {
   vector <bool> isPrime(N + 1, true);
   for (int i = 3; i*2 <= N; i += 2) {
      int p = 0;
      while (1ll * i*(i + p) <= N) isPrime[i*(i + p)] = false, ++p;
   }

   for (int i = 3; i <= N; i += 2) {
      if (isPrime[i]) primes.push_back(i);
   }
}

int solve(int n) {
   return primes[n - 1];
}

signed main() {
   IOS; PREC;
   sieve();
   int tc;
   cin >> tc;
   while(tc--) {
      int n; cin >> n;
      cout << solve(n) << '\n';
   }

   return EXIT_SUCCESS;
}

