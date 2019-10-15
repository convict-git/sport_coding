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
using ff = long double;
using pii = pair<int,int>;

#define debug(args...) { \
/* WARNING : do NOT compile this debug func calls with following flags: // \
 * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) { it->empty();
   cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << fixed << setprecision(15) << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

const int N = 1004, Mod = (int)1e9 + 7;
vector <string> mat;
ll dp[N][N];
int n, m;

inline ll add (ll x, ll y) { return ((x%Mod) + (y%Mod))%Mod; }

void solve() {
   for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j)
      dp[i][j] = 0;

   for (int i = 1; i <= n && mat[i][1] == '.'; ++i) dp[i][1] = 1;
   for (int j = 1; j <= m && mat[1][j] == '.' ; ++j) dp[1][j] = 1;

   for (int i = 2; i <= n; ++i) for (int j = 2; j <= m; ++j)
   {
      if (mat[i][j] != '.') continue;
      dp[i][j] = add(dp[i-1][j], dp[i][j-1]);
   }
   cout << dp[n][m] << '\n';
}

void read() {
   cin >> n >> m;
   mat.push_back(" ");
   for (int i = 1; i <= n; ++i){
      string st; cin >> st;
      st = " " + st;
      mat.push_back(st);
   }
}

signed main() {
   IOS; PREC;
   read(), solve();

   return EXIT_SUCCESS;
}
