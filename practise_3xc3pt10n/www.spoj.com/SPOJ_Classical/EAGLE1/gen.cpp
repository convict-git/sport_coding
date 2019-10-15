#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;

int rand(int l, int h) {
	return l + rand()%(h - l + 1);
}

int main(int argc, char* argv[]) {
	IOS; PREC;
	srand(atoi(argv[1]));
	int tc = 1;
	cout << tc << '\n';
	while (tc--) {
		int n = (int)1e5;
		cout << n << '\n';
		for (int i = 2; i <= n; ++i) {
			cout << 1 << ' ' << i << ' ' << rand(1, (int)1e9) << '\n';
		}
	}

	return EXIT_SUCCESS;
}
