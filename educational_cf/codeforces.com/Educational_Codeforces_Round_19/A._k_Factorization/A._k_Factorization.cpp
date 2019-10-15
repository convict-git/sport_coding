#include      <bits/stdc++.h>
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
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
using   ull = unsigned long long;
using   ff  = long double;
using   pii = pair<int,int>;
using   pil = pair<int,ll>;
typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
   int operator()(pii x) const { return x.x*31 + x.y; }
};
gp_hash_table <pii, int, chash> mp;

#if __cplusplus > 201103L
seed_seq seq{
   (uint64_t) chrono::duration_cast<chrono::nanoseconds>
      (chrono::high_resolution_clock::now().time_since_epoch()).count(),
      (uint64_t) __builtin_ia32_rdtsc(),
      (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]
#else
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rng(seed);
#endif

#define debug(args...) { \
   /* WARNING : do NOT compile this debug func calls with following flags: // \
    * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); \
   istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) {
   it->empty(); cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
   cerr << fixed << setprecision(15)
      << " [ " <<  *it << " : " << a  << " ] "<< ' ';
   err(++it, args...);
}
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
   // cerr << primes.size() << '\n';
}

vector <pii> total_divisors(int n) {
   vector <pii> prime_divisors;
   vector <int> pd; // prime divisors of n
   int td = 1; // total divisors of n
   int n_ref = n;
   for (int p : primes) {
      int cnt_p = 0;
      if (1ll*p*p > 1ll*n_ref) break;
      int alpha = 0;
      if (n % p == 0) {
         pd.push_back(p);
      }
      while (n%p == 0) {
         n/=p, ++alpha;
         ++cnt_p;
      }
      if (cnt_p) prime_divisors.push_back(make_pair(p, cnt_p));
      td *= (1 + alpha);
      powers.push_back(alpha);
   }
   td *= (1 + (n != 1));
   if (n != 1) {
      pd.push_back(n);
      prime_divisors.push_back(make_pair(n, 1));
   }

   return prime_divisors;
}

int n, k;
void solve() {
   sieve();
   vector <pii> factors = total_divisors(n);
   for (auto el : factors) cerr << el.x << ' ' << el.y << '\n';
   int cnt = 0;
   vector <int> ans;
   int cur_prod = 1;
   for (int i = 0; i < (int)factors.size(); ++i) {
      while (cnt < k - 1 && factors[i].y > 0) {
         cur_prod *= factors[i].x;
         ans.push_back(factors[i].x);
         --factors[i].y;
         ++cnt;
      }
   }
   if (cur_prod == n) {
      cout << -1 << '\n';
   }
   else {
      for (int el : ans) cout << el << ' ';
      cout << n/cur_prod << '\n';
   }
}

signed main() {
   IOS; PREC;
   cin >> n >> k;
   solve();

   return EXIT_SUCCESS;
}