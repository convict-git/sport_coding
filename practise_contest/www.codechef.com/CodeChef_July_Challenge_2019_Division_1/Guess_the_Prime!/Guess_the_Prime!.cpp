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
#define bg(x) " [ " << #x << " : " << (x) << " ] "
#define x     first
#define y     second
using   ll  = long long;
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

const int MAX_P = 50;
vector <int> primes = {2}, powers;
void sieve() {
   vector <bool> isPrime(MAX_P + 1, true);
   for (int i = 3; i*2 <= MAX_P; i += 2) {
      int p = 0;
      while (1ll*i*(i + p) <= MAX_P)
         isPrime[i*(i + p)] = false, ++p;
   }
   for (int i = 3; i <= MAX_P; i += 2) {
      if (isPrime[i]) primes.push_back(i);
   }
   // cerr << primes.size() << '\n';
}

int total_divisors(int n) {
   int td = 1;
   int n_ref = n;
   for (int p : primes) {
      if (1ll*p*p > n_ref) break;
      int alpha = 0;
      while (n%p == 0) n/=p, ++alpha;
      td *= (1 + alpha);
      powers.push_back(alpha);
   }
   td *= (1 + (n != 1));
   return td;
}
vector <vector <int>> adj;

signed main() {
   IOS; PREC;
   sieve();

   bool ok = false;
   string out;
   for (int p : primes) {
      if (p * p > 50) break;
      cout << p * p << endl;
      cin >> out;
      if (out == "yes") {
         cout << "composite" << endl;
         ok = true;
         break;
      }
   }
   int cnt = 0;
   if (!ok) {
      for (int p : primes) {
         cout << p << endl;
         cin >> out;
         if (out == "yes") {
            ++cnt;
            if (cnt == 2) {
               cout << "composite" << endl;
               break;
            }
         }
      }
   }
   if (!ok) cout << "prime" << endl;
   return EXIT_SUCCESS;
}
