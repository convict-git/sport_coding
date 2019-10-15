#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;

const int N = 55;
const int infi = (int)1e9;
int h, w, mx;
int W[N][N], memo[N][N];
int dx[] = {1, -1, 0}, dy[] = {1, -1, 0};

inline bool valid (int i, int j) {
	return i >= 0 && j >= 0 && i < h && j < w;
}
inline bool prv (int i, int j, int ii, int jj) {
	return W[i][j] == char(1 + W[ii][jj]);
}

void read() {
	string s;
	for (int r = 0; r < h; ++r) {
		cin >> s;
		for (int c = 0; c < w; ++c) {
			W[r][c] = s[c];
		}
	}
}

int dp (int si, int sj) {
	if (W[si][sj] == 'A') return 1;
	else if (memo[si][sj] != -1) return memo[si][sj];
	else {
		memo[si][sj] = -infi;
		for (int ii = 0; ii < 3; ++ii) {
			for (int jj = 0; jj < 3; ++jj) {
				int Si = si + dx[ii], Sj = sj + dy[jj];
				if (valid(Si, Sj) && prv(si, sj, Si, Sj)) {
					nax(memo[si][sj], dp (Si, Sj) + 1);
				}
			}
		}
		return memo[si][sj];
	}
}

void solve(int tc) {
	for (int r = 0; r < h; ++r)
		for (int c = 0; c < w; ++c)
			memo[r][c] = -1;

	mx = 0;
	for (int r = 0; r < h; ++r)
		for (int c = 0; c < w; ++c)
			nax(mx, dp(r, c));
	cout << "Case " << tc << ": " << mx << '\n';
}

void waste(int a, int b) {
	int n, A[N];
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> A[i];
	}
}

int main() {
	IOS; PREC;
	int tc = 0;
	while (cin >> h >> w, h || w) {
      ++tc;
      read();
      solve(tc);
   }

	return EXIT_SUCCESS;
}
