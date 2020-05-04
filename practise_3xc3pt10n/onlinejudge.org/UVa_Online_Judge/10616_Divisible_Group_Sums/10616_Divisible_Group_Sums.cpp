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
using ld = long double;
using pii = pair<int,int>;

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
const int N = 200, M = 10, D = 20;
int dp[N+1][M+1][D+1];
vector <int> ar;
int n, m, d, q;

void dp_solve() {
   //base case
   for (int i = 0; i <= n; ++i) {
      for (int j = 0; j <= m; ++j) {
         for (int k = 0; k < d; ++k) {
            if (k > 0) dp[i][0][k] = 0; // cannot chose any item and get k > 0 // NOT POSSIBLE
            if (k > 0) dp[0][j][k] = 0; // not allowed any item to chose from to get k > 0 // NOT POSSIBLE
            if (j > i) dp[i][j][k] = 0; // chosing more items than given items // NOT POSSIBLE
            dp[i][0][0] = 1; // Chosing none to get k == 0 from i items always possible -- chose none (1 way)
         }
      }
   }

   //recurrence
   for (int i = 1; i <= n; ++i)
      for (int j = 1; j <= m; ++j)
         for (int k = 0; k < d; ++k)
            dp[i][j][k] = dp[i-1][j][k] + dp[i-1][j-1][((k - ar[i]%d + d)%d)];

   // dp(i,j,k) := chose j items from i to get remainder of sum to be k
   // either don't chose ith item so dp(i-1,j,k) i.e. solve with upto i-1 items
   // or chose ith items so dp(i-1,j-1,remaining remainder) i.e. solve with upto i-1
   // // // by chosing j-1 items from i-1 and get remainder that is left after taking ith item
}
void read(int tc) {
   ar.assign(n+1, 0);
   for (int i = 1; i <= n; ++i) cin >> ar[i];
   cout << "SET " << tc << ":\n";
   for (int iq = 1; iq <= q; ++iq) {
      cout << "QUERY " << iq << ": ";
      cin >> d >> m;
      dp_solve();
      cout << dp[n][m][0] << '\n';
   }
}

signed main() {
   IOS; PREC;
   int tc = 0;
   while (cin >> n >> q, n || q) read(++tc);
   return EXIT_SUCCESS;
}
