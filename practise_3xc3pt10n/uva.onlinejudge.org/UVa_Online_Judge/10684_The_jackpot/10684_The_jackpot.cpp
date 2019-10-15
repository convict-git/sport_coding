#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ]"
#define x        first
#define y        second
using ll = long long;

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
const int N = (int)1e4 + 10;
vector <int> ar;
int dp[N][2];
int n;

int solve () {
   dp[0][0] = ar[0], dp[0][1] = INT_MIN;
   for (int i = 1; i < n; ++i) {
      dp[i][0] = max(dp[i-1][0],0) + ar[i];
      dp[i][1] = max(dp[i-1][0], dp[i-1][1]);
   }
   return max(dp[n-1][0], dp[n-1][1]);
}

void read() {
   ar.clear();
   for (int i = 0, tmp; i < n; ++i) {
      cin >> tmp;
      ar.push_back(tmp);
   }
}

signed main() {
   IOS; PREC;
   while (cin >> n, n) {
      read();
      int ans = solve();
      if (ans > 0) cout << "The maximum winning streak is " << ans << ".\n";
      else cout << "Losing streak.\n";
   }

   return EXIT_SUCCESS;
}

