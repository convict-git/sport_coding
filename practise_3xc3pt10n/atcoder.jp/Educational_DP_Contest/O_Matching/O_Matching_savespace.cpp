#include         <bits/stdc++.h>
using namespace std;
#ifndef CONVICTION
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ] "
#define x        first
#define y        second
using ll = long long;
using ff = long double;
using pii = pair<int,int>;

#define debug(args...) { \
/* WARNING : do NOT compile this debug func calls with following flags: // \
 * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) { it->empty();
   cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << fixed << setprecision(15) << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

const int N = 22, MOD = (int)1e9 + 7;

int dp[1 << N];
int ar[N][N];
int n;

inline int add (int a, int b) { return ((a%MOD) + (b%MOD)) % MOD; };
inline int mul (int a, int b) { return int(1ll*a*b % MOD); };

void solve() {
   dp[0] = 0;

   for (int k = 0; k < n; ++k) {
      if (ar[1][k + 1]) dp[1 << k] = 1;
   }

   for (int i = 2; i <= n; ++i) {
      for (int j = (1 << n) - 1; j >= 1; --j) {
         if (__builtin_popcount(j) != i) continue;
         for (int k = 0; k < n; ++k) {
            if (ar[i][k + 1] && (j & (1 << k)))
               dp[j] = add(dp[j], dp[j - (1 << k)]);
         }
      }
   }
   int total = dp[(1 << n) - 1];
   cout << total << '\n';
}

signed main() {
   IOS; PREC;
   cin >> n;
   for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= n; ++j)
         cin >> ar[i][j];
   solve();

   return EXIT_SUCCESS;
}


