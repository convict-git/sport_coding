#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include <cassert>
#include <ctime>
#include <set>
#include <map>

using namespace std;

#ifdef WIN32
	#define LLD "%I64d"
#else
	#define LLD "%lld"
#endif


typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<ll> vll;
typedef vector<vll> vvll;

#define TASKNAME "text"
#define pb push_back
#define mp make_pair
#define EPS (1E-9)
#define INF ((int)1E9)
#define sqr(x) ((x) * (x))
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define sz(x) ((int)(x).size())

const int maxn = (int)1e5;
int nxt[maxn][2];
int a[maxn], b[maxn - 1];

int main() {
	#ifdef DEBUG
		freopen(TASKNAME".in", "r", stdin);
		freopen(TASKNAME".out", "w", stdout);
	#endif

	int n, m;
	while (scanf("%d%d", &n, &m) >= 1) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			if (i)
				b[i - 1] = a[i] - a[i - 1];
		}
		--n;

		int cur[2] = {n, n};
		nxt[n][0] = nxt[n][1] = n;
		for (int i = n - 1; i >= 0; i--) {
			if (b[i] > 0)
				cur[1] = i;
			if (b[i] < 0)
				cur[0] = i;
			nxt[i][0] = cur[0], nxt[i][1] = cur[1];
		}

		for (int iter = 0; iter < m; iter++) {
			int l, r;
			scanf("%d%d", &l, &r);
			--l, --r;
			int v = nxt[l][0];
			v = nxt[v][1];
// 			eprintf("%d %d  %d\n", l, r, v);
			printf(v >= r ? "Yes\n" : "No\n");
		}
	}
	return 0;
}
