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
const int W = (int)2e4 + 10, N = 101, infi = (int)1e9;
int dp[W], n, m;
vector <int> coins;
int memo[N][W];

void solve_without_rep() {
   for (int i = 0; i <= n; ++i)
      for (int w = 0; w <= W; ++w)
         memo[i][w] = infi;

   for (int i = 0; i <= n; ++i) memo[i][0] = 0;

   for (int i = 1; i <= n; ++i) for (int w = 1; w < W; ++w)
   {
      memo[i][w] = memo[i-1][w];
      if (w >= coins[i])
         memo[i][w] = min(memo[i][w], memo[i-1][w-coins[i]] + 1);
   }

   while (m < W && memo[n][m] == infi) ++m;
   cout << m << ' ' << memo[n][m] << '\n';
}

void solve() { // with repetition
   for (int w = 0; w < W; ++w) dp[w] = infi;
   dp[0] = 0;

   for (int i = 1; i <= n; ++i) for (int w = 0; w < W; ++w)
   {
      if (w >= coins[i]) dp[w] = min(dp[w], dp[w-coins[i]] + 1);
   }

   while (m < W && dp[m] == infi) ++m;
   cout << m << ' ' << dp[m] << '\n';
}

void read() {
   cin >> m >> n;
   coins.assign(n+1,0);
   for (int i = 1; i <= n; ++i) cin >> coins[i];
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   while (tc--) read(), solve_without_rep();

   return EXIT_SUCCESS;
}
