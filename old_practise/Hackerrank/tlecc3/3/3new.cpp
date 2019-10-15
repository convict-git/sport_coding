#include <bits/stdc++.h>
using namespace std;
const int maxn = 301;
const int inf = (int) 1e9;

int rows, col;
char Ar[maxn][maxn];
int dp[maxn][maxn][3];
int vis[maxn][maxn][3];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
pair <int, int> startVer, endVer;
long long cnt = 0;

int solver (int sr, int sc, int K) {
	// cerr << sr << ' ' << sc << ' ' << K << '\n';
	cnt++;
	// cerr << "Count " << cnt << '\n';
	if (vis[sr][sc][K] == 1) {
		return dp[sr][sc][K];
	}
	else {
		int ret = inf;
		for (int rot = 0; rot < 4; ++rot) {
			int Dx, Dy;
			bool ok = true, found = false;
			for (int k = 1; k <= K + 1; ++k) {
				Dx = sr + k * dx[rot];
				Dy = sc + k * dy[rot];
				if (Dx < 0 || Dx >= rows || Dy < 0 || Dy >= col) {
					ok = false;
					break;
				}
				else if (Ar[Dx][Dy] == '#') {
					ok = false;
					break;
				}
				else if (Ar[Dx][Dy] == 'E') {
					found = true;
					break;
				}
			}
			if (found) {
				dp[sr][sc][K] = 1;
			}
			else if (ok) {
				ret = min (ret, solver (Dx, Dy, (K + 1)%3));
			}
		}
		vis[sr][sc][K] = 1;
		dp[sr][sc][K] = ret + 1;
		return dp[sr][sc][K];
	}
}

void solve() {
	int ansme = solver (startVer.first, startVer.second, 0);
	if (ansme == inf) cout << "NO\n";
	else cout << ansme << '\n';
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		cin >> rows >> col;
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < col; ++c) {
				for (int j = 0; j <3; ++j) {
					vis[r][c][j] = 0;
				}
				cin >> Ar[r][c];
				if (Ar[r][c] == 'S') {
					startVer = {r, c};
				}
				else if (Ar[r][c] == 'E') {
					endVer = {r, c};
					for (int k = 0; k < 3; ++k)
						dp[r][c][k] = 0;
				}
			}
		}
		solve();
	}


	return EXIT_SUCCESS;
}


