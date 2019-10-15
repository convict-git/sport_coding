#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
using namespace std;

const int inf = 1e9;
const int maxn = 1000;
int x[3], y[3];

int sx, sy;

inline int dist (int p, int q, int a, int b) {
	return abs (p - a) + abs (q - b);

}

void findShortest() {
	int sd = inf;
	for (int i = 0; i <= maxn; ++i) {
		for (int j = 0; j <= maxn; ++j) {
			int tmp = 0;
			for (int k = 0; k < 3; ++k) {
				tmp += dist (i, j, x[k], y[k]);
			}
			if (tmp < sd) sd = tmp, sx = i, sy = j;
		}
	}
}

void solve() {
	set < pair <int ,int> > S;
	auto grey = [&] (int xx, int yy) {
		S.insert ({xx, yy});
		while (xx != sx) {
			xx > sx ? --xx : ++xx;
			S.insert ({xx, yy});
		}
		while (yy != sy) {
			yy > sy ? --yy : ++yy;
			S.insert ({xx, yy});
		}
	};
	for (int i = 0; i < 3; ++i)
		grey (x[i], y[i]);

	cout << (int) S.size() << '\n';
	for (auto s : S)
		cout << s.first << ' ' << s.second << '\n';
}

int main() {
	IOS; PREC;
	for (int i = 0; i < 3; ++i) {
		cin >> x[i] >> y[i];
	}
	findShortest();
	solve();

	return EXIT_SUCCESS;
}
