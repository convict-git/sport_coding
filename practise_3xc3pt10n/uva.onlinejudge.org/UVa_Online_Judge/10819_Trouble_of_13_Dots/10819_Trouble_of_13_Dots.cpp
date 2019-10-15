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
const int N = 105, W = (int)1e4 + 10;
const int infi = (int)1e9;
int p[N], f[N], dp[N][W], wgt[N][W];
int n, m;

void solve() {
   //dp[i][j] := max value attained from i object whose weight adds up exactly to j
   //wgt[i][j] := wgt either 0 or j
   for (int i = 0; i <= n; ++i) dp[i][0] = 0, wgt[i][0] = 0;
   for (int j = 0; j <= m+200; ++j) dp[0][j] = 0, wgt[0][j] = 0;

   for (int i = 1; i <= n; ++i) for (int j = 0; j <= m+200; ++j)
   {
      dp[i][j] = 0, wgt[i][j] = 0;
      if (j >= p[i] && wgt[i-1][j-p[i]] == j-p[i]) {
         if (dp[i][j] < dp[i-1][j-p[i]] + f[i]) {
            dp[i][j] = dp[i-1][j-p[i]] + f[i];
            wgt[i][j] = j;
         }
      }
      if (wgt[i-1][j] == j) {
         if (dp[i][j] < dp[i-1][j]) {
            dp[i][j] = dp[i-1][j];
            wgt[i][j] = j;
         }
      }
   }
   int mx_val = 0;
   for (int i = 0; i <= m; ++i) mx_val = max(mx_val, dp[n][i]);
   if (m+200 > 2000)
      for (int i = 2001; i <= m+200; ++i) mx_val = max(mx_val, dp[n][i]);
   cout << mx_val << '\n';
}

void read() {
   for (int i = 1; i <= n; ++i) cin >> p[i] >> f[i];
}

signed main() {
   IOS; PREC;
   while (cin >> m >> n) read(), solve();

   return EXIT_SUCCESS;
}
