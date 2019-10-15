/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows * * * * * * */
#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;
using pii=pair <int, int>;

/*HackItAndHaveIt*/

const int N = (int)1e3 + 10;
const int infi = (int)1e9;
char M[N][N];
int n, m, k;
int px, py;
int dx[] = {1, 0, 0, -1};
int dy[] = {0, -1, 1, 0};
char mov[] = {'D', 'L', 'R', 'U'};

inline bool isValid (int ii, int jj) {
	return ii >= 0 && jj >= 0 && ii < n && jj < m && M[ii][jj] != '*';
}

void solve() {
	bool used[N][N];
	int dist[N][N];
	queue <pii> q;
	q.push({px, py});

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			dist[i][j] = infi, used[i][j] = false;
	dist[px][py] = 0;
	used[px][py] = true;

	while (!q.empty()) {
		pii u = q.front();
		q.pop();
		int Sx, Sy;
		for (int ii = 0; ii < 4; ++ii) {
			Sx = u.x + dx[ii], Sy = u.y + dy[ii];
			if (isValid(Sx, Sy) && used[Sx][Sy] == false) {
				q.push(pii(Sx, Sy));
				dist[Sx][Sy] = dist[u.x][u.y] + 1;
				used[Sx][Sy] = true;
			}
		}
	}

	int sx = px, sy = py, Sx, Sy;
	vector <char> Path;
	for (int s = 0; s < k; ++s) {
		bool ok = false;
		for (int ii = 0; ii < 4; ++ii) {
			Sx = sx + dx[ii], Sy = sy + dy[ii];
			if (isValid(Sx, Sy) && dist[Sx][Sy] <= k - s - 1) {
				ok = true;
				Path.push_back(mov[ii]);
				sx = Sx, sy = Sy;
				break;
			}
		}
		if (!ok) {
			cout << "IMPOSSIBLE\n";
			return;
		}
	}
	for (auto p : Path) cout << p;
	cout << '\n';
}

void read() {
	cin >> n >> m >> k;
	string s;
	for (int r = 0; r < n; ++r) {
		cin >> s;
		for (int c = 0; c < m ; ++c) {
			M[r][c] = s[c];
			if (M[r][c] == 'X') px = r, py = c;
		}
	}
	if (k & 1) cout << "IMPOSSIBLE\n";
	else solve();
}

int main() {
	IOS; PREC;
	read();

	return EXIT_SUCCESS;
}

