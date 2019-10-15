#include         <iostream>
#include         <iomanip>
#include         <functional>
#include         <algorithm>
#include         <vector>
#include         <map>
#include         <set>
#include         <string>
#include         <cstring>
#include         <climits>
#include         <cstdlib>
#include         <cmath>
#include         <iomanip>
#include         <cassert>
#define pb       push_back
#define eb       emplace_back
#define se       second
#define fi       first
#define all(v)   (v).begin(),(v).end()
#define bug(s,x) fprintf(stderr,"[%s %s : %i]\n",s,#x,x),fflush(stderr)
#define bg(x)    bug ("bug : ", x)
#define inf      (0x7fffffff)
#define eps      ((double)1e-9)
#define scanf    warnscanf_shit = scanf
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed

using namespace std;
int warnscanf_shit;
typedef long long ll;
typedef unsigned long long ull;
const int MOD = 1e9 + 7;
const int MAXN = 1e2 + 10;
int n, k, d;
ll dp[MAXN][2] = {0}, sol = 0;
inline void add (ll &x, const ll &y) { x = (x + y)%MOD; }

void solve() {
  dp[0][0] = 1, dp[0][1] = 0;
  bool have = 1;

  for (int init = 1; init <= n; ++init) {
	 for (int rem = 1; rem <= min (d - 1, k); ++rem) {
		if (init < rem) break;
		add (dp[init][!have], dp[init - rem][!have]);
		add (dp[init][have], dp[init - rem][have]);
	 }

	 for (int rem = min (d, k); rem <= min (init, k); ++rem) {
		if (init < rem) break;
		add (dp[init][have], dp[init - rem][have]);
		add (dp[init][have], dp[init - rem][!have]);
	 }
  }

  cout << dp[n][have] << '\n';
}

int main() {
  IOS; PREC;
  cin >> n >> k >> d;
  assert (d <= k && n <= 100 && k <= 100);
  solve();
  return EXIT_SUCCESS;
}

