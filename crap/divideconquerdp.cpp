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

#define debug(args...) \
{ \
/* WARNING : do NOT compile this debug func calls with following flags: // \
 * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); \
   istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it)
{
   it->empty(); cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args)
{
	cerr << fixed << setprecision(15)
      << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

const int M = 4e3 + 10, N = 1e3 + 10;
const ll inf = (ll) 1e18;
ll dp[M][N];
int ar[N];
ll pref[N];
int n, m;
//dp[i][j] := min cost to divide 1...j in i consecutive groups such that
//squares of sum of group wgt is min
//dp[i][j] = min of k { dp[i-1][k] + C[k+1][j] }
//C[k+1][j] = (pref[j] - pref[k])^2

void compute (int i, int l, int r, int opt_l, int opt_r)
{
   if (l < r) return;
   int mid = (l + r)/2;
   // to calc for mid go from opt_l, opt_r

   int opt_k = -1;
   dp[i][mid] = inf;
   for (int k = opt_l; k <= opt_r; ++k) {
      int new_g = dp[i-1][k] + (pref[mid] - pref[k])*(pref[mid] - pref[k]);
      if (dp[i][mid] > new_g) {
         dp[i][mid] = new_g;
         opt_k = k;
      }
   }
   compute(i, l, mid - 1, opt_l, opt_k);
   compute(i, mid + 1, r, opt_k, opt_r);
}

void naive_solve()
{
   //base case
   for (int i = 0; i <= m; ++i) {
      dp[i][0] = 0;
   }
   for (int j = 0; j <= n; ++j) {
      dp[0][j] = 0;
   }

   for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
         dp[i][j] = inf;
         for (int k = 1; k < j; ++k) {
            dp[i][j] = min(dp[i][j],
                  dp[i-1][k] + (pref[j] - pref[k])*(pref[j] - pref[k]));
         }
      }
   }
}

void read() {
   cin >> n >> m;
   pref[0] = 0;
   for (int i = 1; i <= n; ++i) {
      cin >> ar[i];
      pref[i] = pref[i-1] + ar[i];
   }
}

signed main()
{
   IOS; PREC;
   return EXIT_SUCCESS;
}

