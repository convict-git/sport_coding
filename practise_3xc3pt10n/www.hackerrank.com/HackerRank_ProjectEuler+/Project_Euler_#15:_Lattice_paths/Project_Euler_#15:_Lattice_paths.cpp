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
const int N = 505;
const int Mod = (int)1e9 + 7;
using ll = long long;
ll dp[N + 1][N];
int n, m;

inline ll add (const ll &a, const ll &b) {
   return ((a%Mod) + (b%Mod))%Mod;
}

void precalc() {
   for (int i = 0; i < N + 1; ++i) dp[i][0] = i + 1;
   for (int j = 0; j < N; ++j) dp[0][j] = 1;

   for (int j = 1; j < N; ++j)
      for (int i = 1; i < N + 1; ++i)
         dp[i][j] = add(dp[i - 1][j], dp[i][j - 1]);
}

signed main() {
   IOS; PREC;
   precalc();
   int tc; cin >> tc;
   while (tc--) {
      cin >> n >> m;
      cout << dp[n][m - 1] << '\n';
   }

   return EXIT_SUCCESS;
}

