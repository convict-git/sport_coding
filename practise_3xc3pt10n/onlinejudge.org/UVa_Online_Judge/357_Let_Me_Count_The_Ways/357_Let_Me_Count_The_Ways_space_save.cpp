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

const int N = 30010*100;
int coins[] = {0, 1, 5, 10, 25, 50};
ll dp[N];

void solve() {
   dp[0] = 1;

   for (int i = 1; i < 6; ++i) for (int j = 1; j < N; ++j)
         if (j >= coins[i]) dp[j] += dp[j-coins[i]];
}

void read() {
   solve();
   int n;
   while (cin >> n) {
      ll ans = dp[n];
      if (ans == 1)
         cout << "There is only 1 way to produce " << n << " cents change.\n";
      else cout << "There are " << ans << " ways to produce " << n << " cents change.\n";
   }
}

signed main() {
   IOS; PREC;
   read();
   return EXIT_SUCCESS;
}
