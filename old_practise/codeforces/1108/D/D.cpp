#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
using namespace std;

const int N = (int) 2e5 + 10;
int n;
string S;
int memo[N][3];
int pr[N][3] = {0};
map <char, int> mp1;
map <int, char> mp2;

int dp (int i, int mode) {
	if (i < 0) return 0;
	if (memo[i][mode] != -1) return memo[i][mode];
	int mn = INT_MAX;
	for (int j = 0; j < 3; ++j) {
		if (j == mode) continue;
		if (mn >= (dp(i - 1, j) + (mode != mp1[S[i]]))) {
			mn = dp (i - 1, j) + (mode != mp1[S[i]]);
			pr[i][mode] = j;
		}
	}
	return memo[i][mode] = mn;
}

void init() {
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < 3; ++j)
			pr[i][j] = memo[i][j] = -1;
	mp1 = {{'R', 0}, {'G', 1}, {'B', 2}};
	mp2 = {{0, 'R'}, {1, 'G'}, {2, 'B'}};
}

void makeString() {
	int mn = INT_MAX, tk = 0;
	for (int j = 0; j < 3; ++j) {
		if (mn >= memo[n - 1][j])
			mn = memo[n - 1][j], tk = j;
	}
	int i = n - 1, mode = tk;
	if (S[i] != mp2[mode]) S[i] = mp2[mode];

	while (i > 0 && pr[i][mode] != -1) {
		mode = pr[i][mode];
		--i;
		if (S[i] != mp2[mode]) S[i] = mp2[mode];
	}
}


int main() {
	IOS; PREC;
	cin >> n >> S;
	assert ((int)S.size() == n);
	init();
	cout << min ({dp (n - 1, 0), dp (n - 1, 1), dp (n - 1, 2)}) << '\n';
	makeString();
	cout << S << '\n';

	return EXIT_SUCCESS;
}
