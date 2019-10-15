#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
using namespace std;

int main() {
	//IOS; PREC;
	int n, k;
	cin >> n >> k;

	for (int x = 0; x < (int)1e9; ++x) {
		long long x_ = (1ll*x)/k;
		if (x_*x_*k + n == x_*x) {
			cout << x << '\n';
			break;
		}
	}

	return EXIT_SUCCESS;
}
