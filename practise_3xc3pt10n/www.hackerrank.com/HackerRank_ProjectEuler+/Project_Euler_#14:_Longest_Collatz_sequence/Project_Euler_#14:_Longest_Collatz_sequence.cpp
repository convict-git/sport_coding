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

#define debug(args...) { \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) { it->empty();
   cerr << " (Line : " << __LINE__ << ") " << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

const int N = (int)5e6 + 10;
int dp[N + 1], memo[N + 1];

int solve(long long n) {
   if (n <= N) {
      if (n == 1) return 0;
      if (memo[n] != -1) return memo[n];
      if (n & 1) return memo[n] = solve(3*n + 1) + 1;
      else return memo[n] = solve(n/2) + 1;
   }
   else {
      int ctr = 0;
      while (n > N) {
         if (n & 1) n = 3*n + 1;
         else n = n/2;
         ++ctr;
      }
      return ctr + solve(n);
   }
}

void precalc() {
   for (int i = 1; i <= N; ++i) memo[i] = -1;

   int cur_max = 0;
   for (int i = 1; i <= N; ++i) {
      if (memo[i] == -1) memo[i] = solve(i);
      if (i == 1) dp[i] = i;
      else {
         if (memo[i] >= cur_max) {
            dp[i] = i;
            cur_max = memo[i];
         }
         else dp[i] = dp[i - 1];
      }
   }
}

signed main() {
   IOS; PREC;
   precalc();
   int tc; cin >> tc;
   while (tc--) {
      int n; cin >> n;
      cout << dp[n] << '\n';
   }
   return EXIT_SUCCESS;
}
