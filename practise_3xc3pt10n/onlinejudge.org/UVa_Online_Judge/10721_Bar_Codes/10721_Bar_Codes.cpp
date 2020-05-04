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
const int N = 55;
ll dp[N][N][N];
int n, k, m;

void solve(int mm) {
   for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j)
      dp[i][j][mm] = 0;

   for (int val = 0; val <= mm; ++val) dp[val][1][mm] = 1;

   for (int i = 1; i < N; ++i) {
      for (int j = 2; j <= i; ++j) {
         for (int last = 1; last <= mm; ++last) {
            if (i > last) dp[i][j][mm] += dp[i-last][j-1][mm];
         }
      }
   }
}

signed main() {
   IOS; PREC;
   for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j)
      for (int val = 0; val < N; ++val) dp[i][j][val] = -1;

   while (cin >> n >> k >> m) {
      if (dp[n][k][m] != -1) cout << dp[n][k][m] << '\n';
      else solve(m), cout << dp[n][k][m] << '\n';
   }

   return EXIT_SUCCESS;
}
