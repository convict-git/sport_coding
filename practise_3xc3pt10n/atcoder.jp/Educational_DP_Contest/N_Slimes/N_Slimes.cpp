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
const int N = 405;
const ll inf = (ll) 1e18;

ll dp[N][N], sum[N];
int ar[N];
int n;

void solve() {

   for (int i = 1; i <= n; ++i) dp[i][i] = 0;

   for (int len = 1; len <= n; ++len) {
      for (int i = 1; i + len <= n; ++i) {
         int j = i + len;
         dp[i][j] = inf;
         for (int k = i; k < j; ++k)
            dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + sum[j] - (i > 1 ? sum[i-1] : 0));
      }
   }
   cout << dp[1][n] << '\n';
}

signed main() {
   IOS; PREC;
   cin >> n;

   for (int i = 1; i <= n; ++i) {
      cin >> ar[i];
      if (i == 1) sum[i] = ar[i];
      else sum[i] = sum[i-1] + ar[i];
   }
   solve();


   return EXIT_SUCCESS;
}
