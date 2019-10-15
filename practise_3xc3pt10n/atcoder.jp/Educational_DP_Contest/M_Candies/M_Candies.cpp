#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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

const int MOD = (int)1e9 + 7;
const int K = (int)1e5 + 10, N = 103;
int n, k;
int ar[N];

int dp[K], cum[K];

int add(int a, int b) {
   a += b;
   if (a >= MOD) a -= MOD;
   return a;
}

int sub (int a, int b) {
   a -= b;
   if (a < 0) a += MOD;
   return a;
}

oid solve() {
   for (int i = 1; i <= k; ++i) dp[i] = 0;
   dp[0] = 1;

   for (int i = 1; i <= n; ++i) {
      for (int j = 0; j <= k; ++j) {
         if (j) cum[j] = add(cum[j-1], dp[j]);
         else cum[j] = dp[j];
      }
      for (int j = k; j >= 0; --j) {
         int l = max(0,j-ar[i]), r = j;
         dp[j] = cum[r];
         if (l - 1 >= 0) dp[j]  = sub(dp[j], cum[l-1]);
      }
   }
   cout << dp[k] << '\n';
}


signed main() {
   IOS; PREC;
   cin >> n >> k;
   for (int i = 1; i <= n; ++i) cin >> ar[i];
   solve();

   return EXIT_SUCCESS;
}
