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

const int N = 1004, M = 10, infi = (int)1e9;
int dp[N+1][M];
int cost[] = {20, 30, 60};
int wind[N][M];
int X;


void solve() {
   dp[0][0] = 0;
   for (int h = 1; h < 10; ++h) dp[0][h] = infi;

   for (int w = 1; w <= X; ++w) {
      for (int h = 0; h < 10; ++h) {
         dp[w][h] = infi;
         if (h < 9) dp[w][h] = min(dp[w][h], dp[w-1][h+1] + cost[0] - wind[w][h]);
         dp[w][h] = min(dp[w][h], dp[w-1][h] + cost[1] - wind[w][h]);
         if (h > 0) dp[w][h] = min(dp[w][h], dp[w-1][h-1] + cost[2] - wind[w][h]);
      }
   }
   int mn_cost = dp[X][0];
   cout << mn_cost << '\n' << '\n';
}

void read() {
   cin >> X;
   assert(X%100 == 0);
   X /= 100;
   for (int h = 9; h >= 0; --h)
      for (int w = X; w >= 1; --w)
         cin >> wind[w][h];
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   while (tc--) read(), solve();

   return EXIT_SUCCESS;
}
