#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nin(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;

set <int> qs;
int n;
const int N = (int) 1e6 + 10;
const int infi = 1e9;
//int memo[N][2];

void make() {
	vector <int> v;
	int t = 1;
	while (t <= (int) 1e6) {
		v.push_back (t);
		t *= 10;
	}
	int powersetsize = (1 << 7);
	for (int i = 1; i <= powersetsize; ++i) {
		int tmp = 0;
		for (int j = 0; j < 7; ++j) {
			if (i & (1 << j)) {
				tmp += v[j];
			}
		}
		qs.insert (tmp);
	}
	qs.erase(qs.begin());
}

int dp[N][2];
void solvedp () {
	for (int i = 0; i <= n; ++i)
		dp[i][0] = infi, dp[i][1] = -1;

	dp[0][0] = 0;
	dp[0][1] = -1;

	for (int i = 1; i <= n; ++i) {
		bool ok;
		for (auto s : qs) {
			if (i >= s) {
				ok = nin (dp[i][0], dp[i - s][0] + 1);
				if (ok) dp[i][1] = s;
			}
		}
	}
	cout << dp[n][0] << '\n';
	int idx = n;
	while (dp[idx][1] != -1) {
		cout << dp[idx][1] << ' ';
		idx -= dp[idx][1];
	}
	cout << '\n';
}
/*

int dp (int m) {
	if (m == 0) return 0;
	if (memo[m][0] == -1) {
		int len = infi;
		for (auto s : qs) {
			bool ok = false;
			if (m >= s) {
				ok = nin (len, dp (m - s));
				if (ok) memo[m][0] = len + 1, memo[m][1] = s;
			}
		}
	}
	return memo[m][0];
}

void solve() {
	int len = dp (n),
		i = n;
	vector <int> V;
	cout << len << '\n';
	while (memo[i][1] != -1) {
		V.push_back (memo[i][1]);
		i -= memo[i][1];
	}
	for_each (V.begin(), V.end(), [] (int v) ->void { cout << v << ' '; });
	cout << '\n';
}
*/

int main() {
	IOS; PREC;
	make();
	//for (int i = 0; i < N; ++i) memo[i][0] = -1, memo[i][1] = -1;

	cin >> n;
	//solve();
	solvedp();

	return EXIT_SUCCESS;
}
