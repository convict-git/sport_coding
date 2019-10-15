#pragma GCC      optimize ("Ofast")
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
const int MAXN = 1e5 + 10;

int n;
struct node {
	bool lft, rgt, both;
	int lftCount, rgtCount, noneCount, bothCount;
} dp [MAXN];
struct prop {
	ll x, h;
} tree [MAXN];


void solve() {
	dp[0].rgt = true;
	dp[0].rgtCount = 1;
	dp[n].lft = true;
	for (int i = 1; i <= n; ++i) {
		dp[i].lftCount = max (dp[i - 1].lftCount, dp[i - 1].noneCount) + dp[i].lft;
		dp[i].rgtCount = max ({dp[i - 1].lftCount, dp[i - 1].rgtCount,
				dp[i - 1].noneCount, dp[i - 1].bothCount})
			+ dp[i].rgt;
		dp[i].noneCount = dp[i].rgtCount - dp[i].rgt;
		dp[i].bothCount = dp[i].lftCount - dp[i].lft + 2*dp[i].both;
	}
	int ans = max ({dp[n].lftCount, dp[n].rgtCount, dp[n].noneCount, dp[n].bothCount});
	cout << ans << '\n';
}

int main() {
	//IOS; PREC;

	int x, h;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> x >> h;
		tree[i] = {x, h};
		if (i) {
			dp[i] = {false, false, false, 0, 0, 0, 0};
			ll dist = tree[i].x - tree[i - 1].x - 1;
			dp[i].lft = (dist >= tree[i - 1].h);
			dp[i].rgt = (dist >= tree[i].h);
			dp[i].both = (dist >= tree[i].h + tree[i - 1].h);
		}
	}
	solve();
	return EXIT_SUCCESS;
}

