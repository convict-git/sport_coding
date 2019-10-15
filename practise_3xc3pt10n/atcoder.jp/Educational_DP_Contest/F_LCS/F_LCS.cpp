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

const int N = 3004;
int dp[N][N];
string s, t;
int n, m;

void solve() {
   for (int i = 0; i <= n; ++i) dp[i][0] = 0;
   for (int j = 0; j <= m; ++j) dp[0][j] = 0;

   for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
   {
      if (s[i] == t[j]) dp[i][j] = dp[i-1][j-1] + 1;
      else {
         if (dp[i-1][j] > dp[i][j-1]) dp[i][j] = dp[i-1][j];
         else dp[i][j] = dp[i][j-1];
      }
   }

   string longest_ssq = "";
   int i = n, j = m;
   while (i && j) {
      if (s[i] == t[j]) longest_ssq += s[i], --i, --j;
      else if (dp[i][j] == dp[i-1][j]) --i;
      else --j;
   }
   reverse(longest_ssq.begin(), longest_ssq.end());
   cout << longest_ssq << "\n";
}

signed main() {
   IOS; PREC;
   cin >> s >> t;
   n = (int)s.size(), m = (int)t.size();
   s = " " + s, t = " " + t;
   solve();

   return EXIT_SUCCESS;
}
