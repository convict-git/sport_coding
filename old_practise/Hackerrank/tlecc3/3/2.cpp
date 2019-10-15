#pragma GCC      optimize ("Ofast")
#include         <iostream>
#include         <iomanip>
#include         <functional>
#include         <algorithm>
#include         <vector>
#include         <map>
#include         <set>
#include         <string>
#include         <cstring>
//#include         <climits>
#include         <cstdlib>
#include         <cmath>
#include         <iomanip>
#include         <cassert>
#include         <queue>
#define pb       push_back
#define eb       emplace_back
#define se       second
#define fi       first
#define all(v)   (v).begin(),(v).end()
#define bug(s,x) fprintf(stderr,"[%s %s : %i]\n",s,#x,x),fflush(stderr)
#define bg(x)    bug ("bug : ", x)
#define inf      (0x7fffffff)
#define eps      ((double)1e-9)
#define scanf    warnscanf_shit = scanf
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed

using namespace std;
int warnscanf_shit;
typedef long long ll;
typedef unsigned long long ull;
const int MOD = 1e9 + 7;
const int maxn = 1e5 + 10;

inline long long fast_input(void) {
    char t;
    long long x = 0, neg = 0;
    t = getchar();
    while ((t < 48 || t > 57) && t != '-') t = getchar();
    if (t == '-') {
        neg = 1;
        t = getchar();
    }
    while (t >= 48 && t <= 57) {
        x = (x << 3) + (x << 1) + t - 48;
        t = getchar();
    }
    if (neg) x = -x;
    return x;
}

inline void fast_output(long long x, int mode) {
    char a[20]; long long i = 0, j; a[0] = '0';
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x == 0) putchar('0');
    while (x) {
        a[i++] = x % 10 + 48;
        x /= 10;
    }
    for (j = i - 1; j >= 0; j--) putchar(a[j]);
    if (mode == 0) putchar('\n');
    else putchar(' ');
}

vector < vector <int> > Adj;
int t = 0;
int d[maxn];
int pr[maxn];
int rnk[maxn];
int sz[maxn];

int findSet (int x) {
	while (x != pr[x]) x = pr[x];
	return x;
}

int findSetSize (int x) {
	while (x != pr[x]) x = pr[x];
	return sz[x];
}


void mergeSet (int x, int y) {
	int repx = findSet (x);
	int repy = findSet (y);

	if (rnk[repx] > rnk[repy]) {
		pr[repy] = repx;
		sz[repx] += sz[repy];
		sz[repy] = 0;
	}
	else {
		pr[repx] = repy;
		sz[repy] += sz[repx];
		sz[repx] = 0;
	}
	if (rnk[repx] == rnk[repy]) {
		++rnk[repy];
	}
}

int n, x, y;
void createSet () {
	for (int i = 1; i <= n; ++i) {
		pr[i] = i;
		rnk[i] = 0;
		sz[i] = 1;
	}
}

void dijkstra (int src, int trg) {
	set < pair <int, int> > Q;

	for (int i = 1; i <= n; ++i) {
		if (findSetSize (i) != 0) {
			d[i] = (i == src ? 0 : inf);
			Q.insert ({d[i], i});
		}
	}

	while (!Q.empty()) {
		int u = Q.begin()->second;
		int len = Q.begin()->first;
		if (len == inf) break;
		Q.erase (Q.begin());

		for (auto ver : Adj[u]) {
			if (d[ver] > len + findSetSize (u)) {
				d[ver] = len + findSetSize (u);
				Q.insert ({d[ver], ver});
			}
		}
	}

	if (d[trg] == inf) {
		cout << -1 << '\n';
	}
	else cout << d[trg] << '\n';
}

int pathRecover[maxn];
ll cost = 0;
void bfs (int src, int trg) {
    for (int i = 1; i <= n; ++i) {
		if (findSetSize (i) != 0) {
			d[i] = (i == src ? 0 : inf);
		}
    }

    queue <int> Q;
    Q.push (src);

    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (auto v : Adj[u]) {
            if (d[v] > d[u] + findSetSize (u)) {
                d[v] = d[u] + findSetSize (u);
                pathRecover[v] = u;
                Q.push (v);
            }
        }
    }

    int tmp = trg;
    if (d[trg] == inf) cout << "-1\n";
    else if (src == trg) cout << 0 << '\n';
    else  {
        while (tmp != src)  {
            tmp = pathRecover[tmp];
            cost += (long long) findSetSize (tmp);
        }
        cout << cost << '\n';
    }
}

int main() {
	IOS; PREC;
	cin >> n >> x >> y;
	int m1, m2;
	cin >> m1;
	int u, v;
	createSet ();

	while (m1--) {
		cin >> u >> v;
		mergeSet (u, v);
	}

	Adj.resize (n + 1);
	cin >> m2;

	while (m2--) {
		cin >> u >> v;
		int _u = findSet (u);
		int _v = findSet (v);
		Adj[_u].push_back (_v);
		assert (_u <= n && _v <= n);
	}

	bfs (findSet (x), findSet (y));
	//dijkstra (findSet (x), findSet (y));
	return 0;
}
