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
//Don’t practice until you get it right. Practice until you can’t get it wrong

const int MAX_P = 8191;
vector <int> primes = {2}, powers;
void sieve() {
   vector <bool> isPrime(MAX_P + 1, true);
   for (int i = 3; i*2 <= MAX_P; i += 2) {
      int p = 0;
      while (1ll * i*(i + p) <= MAX_P)
         isPrime[i*(i + p)] = false, ++p;
   }
   for (int i = 3; i <= MAX_P; i += 2) {
      if (isPrime[i]) primes.push_back(i);
   }
}

const int Mod = (int)1e9 + 7;
inline int add (int x, int y) {
   return (x + y) % Mod;
}
inline int mul (int x, int y) {
   return int(1ll*x*y % Mod);
}

signed main() {
   IOS; PREC;
   sieve();
   int tc;
   cin >> tc;
   while (tc--) {
      vector <int> fq(4550);
      vector <int> a;
      int n;
      cin >> n;
      for (int i = 0; i < n; ++i) {
         int foo;
         cin >> foo;
         if (fq[foo] == 0) {
            a.push_back(foo);
         }
         ++fq[foo];
      }

      n = (int)a.size();
      vector <int[8192]> dp(n + 1);

      dp[0][0] = 1;

      for (int i = 0; i < n; ++i) {
         int odd_n = fq[a[i]]/2 + (fq[a[i]] & 1);
         int even_n = fq[a[i]]/2 + 1;
         for (int j = 0; j < 8192; ++j) {
            dp[i + 1][j ^ a[i]] = add(dp[i + 1][j ^ a[i]], mul(dp[i][j], odd_n));
            dp[i + 1][j] = add(dp[i + 1][j], mul(dp[i][j], even_n));
        }
      }

      int ans = 0;
      for (int p : primes) {
         ans = add(ans, dp[n][p]);
      }
      cout << ans << "\n";
   }

   return EXIT_SUCCESS;
}
