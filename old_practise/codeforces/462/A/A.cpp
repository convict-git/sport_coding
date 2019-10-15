#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;

const int N = 100 + 10;
int W[N][N];
int n;
inline int getW (int i, int j) {
	return (i < 0 || i >= n || j < 0 || j >= n ? 0 : W[i][j]);
}


int main() {
	IOS; PREC;
	string s;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> s;
		for (int j = 0; j < n; ++j) {
			W[i][j] = (s[j] == 'x' ? 0 : 1);
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (getW (i + 1, j) ^ getW (i - 1, j) ^ getW (i, j + 1) ^ getW (i, j - 1)) {
				puts("NO");
				return 0;
			}
		}
	}
	puts ("YES");

	return EXIT_SUCCESS;
}
