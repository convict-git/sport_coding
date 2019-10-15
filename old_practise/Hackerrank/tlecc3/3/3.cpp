#include <bits/stdc++.h>
using namespace std;
const int N = 301;

int rows, col;
pair <int, int> startVer, endVer;
char vi[N][N];
int vis[N][N][4][3];
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
bool found = false;
int ans = 0;
vector <pair <int, int> > path;
using pii = pair <int, int>;

void buggerOff (int x, int y, int sr, int sc) {
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < col; ++c) {
				if (x == r && y == c) {
					cerr << "*";
				}
				else if (r == sr && c == sc) {
					cerr << "$";
				}
				else cerr << vi[r][c];
			} cerr << '\n';
		}
		cerr << '\n';
}

void dfs (int sr, int sc, int K) {
	for (int rot = 0; rot < 4; ++rot) {
		int Dx, Dy;
		bool goOn = false;
		for (int k = 1; k <= K + 1; ++k) {
			Dx = sr + k * dx[rot];
			Dy = sc + k * dy[rot];
			if (Dx < 0 || Dx >= rows || Dy < 0 || Dy >= col) {
				goOn = false;
				break;
			}
			char allowed = vi[Dx][Dy];
			if (allowed == '#') {
				goOn = false;
				break;
			}
			if (allowed == 'E') {
				found = true;
				path.push_back ({sr, sc});
				return;
			}
			goOn = true;
		}
		if (goOn && vis[sr][sc][rot][K] == 0) {
			//cerr << "dx " << Dx << ' ' << " dy " << Dy << " Element is " << vi[Dx][Dy] << '\n';
			//cerr << " sr " << sr << ' ' << " sc " << sc << " Rotation " << rot << '\n';
			//buggerOff (Dx, Dy, sr, sc);
			vis[sr][sc][rot][K] = 1;
			dfs (Dx, Dy, (K+1)%3);
		}

		if (found == true) {
			path.push_back ({sr, sc});
			//cerr << " sr " << sr << ' ' << " sc " << sc << " Rotation " << rot << '\n';
			//cerr << "ans is " << ans << '\n';
			return;
		}
	}
}

void solve () {
	ans = 0;
	found = false;
	dfs (startVer.first, startVer.second, 0);
	reverse (path.begin(), path.end());
	for (int i = 0; i < (int) path.size(); ++i) {
		//cerr << path[i].first << ' ' << path[i].second << '\n';
		ans += 1;
		for (int j = (int) path.size() - 1; j >= i + 1; --j) {
			if (path[i] == path[j]) {
				i = j;
			}
		}
	}

	if (found) {
		cout << ans << '\n';
	}
	else cout << "NO\n";
}

int main() {

	int t;
	cin >> t;
	while (t--) {
		cin >> rows >> col;
		for (int r = 0; r < rows; ++r) {
			for (int c = 0; c < col; ++c) {
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j <3; ++j) {
						vis[r][c][i][j] = 0;
					}
				}

				cin >> vi[r][c];
				if (vi[r][c] == 'S') {
					startVer = {r, c};
				}
				else if (vi[r][c] == 'E') {
					endVer = {r, c};
				}
			}
		}
		solve();
	}
	return 0;
}


