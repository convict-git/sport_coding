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
const int N = 41, M = 305, infi = (int)1e9;
int dp[N][M][M];
vector <pii> coins;
int n, S;

void solve() {
   for (int i = 0; i <= n; ++i)
      for (int X = 0; X < M; ++X) for (int Y = 0; Y < M; ++Y)
      {
         dp[i][X][Y] = infi;
      }

   for (int i = 0; i <= n; ++i) dp[i][0][0] = 0;

   for (int i = 1; i <= n; ++i)
      for (int X = 0; X < M; ++X) for (int Y = 0; Y < M; ++Y)
      {
         dp[i][X][Y] = dp[i-1][X][Y];
         if (X >= coins[i].x && Y >= coins[i].y)
            dp[i][X][Y] = min(dp[i][X][Y], dp[i][X-coins[i].x][Y-coins[i].y] + 1);
      }

   int mn_val = infi;
   for (int X = 0; X < M; ++X) for (int Y = 0; Y*Y <= S*S - X*X; ++Y)
   {
      if (X*X + Y*Y != S*S) continue;
      mn_val = min(mn_val, dp[n][X][Y]);
   }
   if (mn_val == infi) cout << "not possible\n";
   else cout << mn_val << '\n';
}

void read() {
   cin >> n >> S;
   coins.assign(n+1, pii());
   for (int i = 1; i <= n; ++i)
      cin >> coins[i].x >> coins[i].y;
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   while (tc--) read(), solve();
   return EXIT_SUCCESS;
}
