#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;
using pii = pair <int, int>;

const int N = 23;
char M[N][N];
int used[N][N];
vector <pii> p;
int m, n;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

inline bool valid(int i, int j) {
	return i >= 0 && j >= 0 && i < m && j < n;
}

inline bool out(int i, int j) {
	bool ok = false;
	for (int ii = 0; ii < 4; ++ii) {
		ok |= (!valid(i + dx[ii], j + dy[ii]));
	}
	return ok;
}

void read() {
	for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) used[i][j] = 0;
	string s;

	cin >> m >> n;
	for (int r = 0; r < m; ++r) {
		cin >> s;
		for (int c = 0; c < n; ++c) {
			M[r][c] = s[c], used[r][c] = 0;
		}
	}
}

bool check() {
	p.clear();
	for (int r = 0; r < m; ++r) {
		for (int c = 0; c < n; ++c) {
			if (M[r][c] == '.') {
				if (out(r, c)) p.push_back({r, c});
			}
		}
	}
	return ((int)p.size() == 2);
}

void dfs (int si, int sj) {
	used[si][sj] = 1;
	for (int ii = 0; ii < 4; ++ii) {
		int Si = si + dx[ii], Sj = sj + dy[ii];
		if (valid(Si, Sj) && used[Si][Sj] == 0 && M[Si][Sj] == '.')
			dfs (Si, Sj);
	}
}

bool solve() {
	dfs(p[0].first, p[0].second);
	return (used[p[1].first][p[1].second] == 1);
}


int main() {
	IOS; PREC;
	int tc;
	cin >> tc;
	while (tc--) {
		read();
		if (check()) {
			if (solve()) puts("valid");
			else puts("invalid");
		}
		else puts("invalid");
	}

	return EXIT_SUCCESS;
}
