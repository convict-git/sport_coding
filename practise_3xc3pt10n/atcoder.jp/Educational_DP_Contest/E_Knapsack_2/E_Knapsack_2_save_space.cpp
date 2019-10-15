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
   stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); \ }
void err(istream_iterator<string> it) { it->empty();
   cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << fixed << setprecision(15) << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

const int N = 105, V = 1004;
const ll inf = (ll) 1e18;

ll dp[N*V];
// dp[v] := min weight attained with knapsack of value exactly v till some iteration
int n, mxv, W;
int w[N], v[N];

void solve() {
   for (int i = 1; i <= mxv; ++i) dp[i] = inf;
   dp[0] = 0;

   for (int i = 1; i <= n; ++i) for (int j = mxv; j >= 0; --j)
   {
      if (j >= v[i]) dp[j] = min(dp[j], dp[j-v[i]] + w[i]);
   }

   int mx_val = 0;
   for (int val = mxv; val >= 0; --val) {
      if (dp[val] <= W) {
         mx_val = val;
         break;
      }
   }
   cout << mx_val << '\n';
}

signed main() {
   IOS; PREC;
   cin >> n >> W;
   mxv = 0;
   for (int i = 1; i <= n; ++i)
      cin >> w[i] >> v[i], mxv += v[i];
   solve();


   return EXIT_SUCCESS;
}
