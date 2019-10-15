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

const int N = (int)1e5 + 10, infi = (int) 1e9;

int dp[N][3], abc[N][3];
int n;

void solve() {
   for (int i = 1; i <= n; ++i) for (int j = 0; j < 3; ++j)
      dp[i][j] = infi;
   dp[1][0] = abc[1][0], dp[1][1] = abc[1][1], dp[1][2] = abc[1][2];

   for (int i = 2; i <= n; ++i) for (int j = 0; j < 3; ++j)
   {
      int mx = max(dp[i-1][(j+1)%3], dp[i-1][(j+2)%3]);
      dp[i][j] = mx + abc[i][j];
   }

   int mx_val = -infi;
   for (int j = 0; j < 3; ++j) {
      mx_val = max(mx_val, dp[n][j]);
   }
   cout << mx_val << '\n';
}

signed main() {
   IOS; PREC;

   cin >> n;
   for (int i = 1; i <= n; ++i) for (int k = 0; k < 3; ++k)
      cin >> abc[i][k];
   solve();

   return EXIT_SUCCESS;
}
