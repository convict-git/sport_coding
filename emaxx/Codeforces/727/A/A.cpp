#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;

long long a, b;
const int infi = (int)1e9;
bool ok = false;
vector <long long> Path;

void dfs (long long x) {
	if (x > infi) return;
	if (x == b) {
		Path.push_back(b);
		ok = true;
		return;
	}
	if (!ok) dfs(2*x);
	if (!ok) dfs(10*x + 1);

	if (ok) Path.push_back(x);
}

void solve() {
	if (ok) {
		printf("YES\n");
		reverse(Path.begin(), Path.end());
		printf("%i\n", (int)Path.size());
		for (auto p : Path) printf("%lld ", p);
		printf("\n");
	}
	else printf("NO\n");
}

int main() {
	IOS; PREC;
	cin >> a >> b;
	dfs(a);
	solve();

	return EXIT_SUCCESS;
}
