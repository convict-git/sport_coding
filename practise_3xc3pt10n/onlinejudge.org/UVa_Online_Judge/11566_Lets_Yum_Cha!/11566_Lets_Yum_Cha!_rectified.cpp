#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (2); cout << fixed
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
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}

const int K = 105, N = 11*2 + 10;
int n, t, x, k, m;
int val[K], cost[K];
int dp[K][N][10000];

void solve() { // outputs max mean favour value with 2 dec (float)
   m = floor(((ld)(n+1)*x*10)/11) - t*(n+1); // max weight

   //base case
   for (int i = 0; i <= k; ++i) for (int j = 0; j <= min(2*k,2*(n+1)); ++j)
      for (int w = 0; w <= m; ++w) dp[i][j][w] = 0;

   // recurrence
   for (int i = 1; i <= k; ++i) for (int j = 1; j <= min(2*k, 2*(n+1)); ++j)
         for (int w = 0; w <= m; ++w)
         {
            dp[i][j][w] = 0;
            nax(dp[i][j][w], dp[i-1][j][w]);
            if (w >= cost[i]) nax(dp[i][j][w], dp[i-1][j-1][w-cost[i]] + val[i]);
            if (w >= 2*cost[i] && j >= 2) nax(dp[i][j][w], dp[i-1][j-2][w-2*cost[i]] + 2*val[i]);
         }

   int mx_val = dp[k][min(2*k,2*(n+1))][m];;
   cout << (ld)mx_val/(n+1) << '\n';
}

void read() {
   for (int i = 1; i <= k; ++i) {
      cin >> cost[i];
      int foo;
      val[i] = 0;
      for (int j = 0; j < n+1; ++j) cin >> foo, val[i] += foo;
   }
}

signed main() {
   IOS; PREC;
   while (cin >> n >> x >> t >> k, n || x || t || k)
      read(), solve();

   return EXIT_SUCCESS;
}
