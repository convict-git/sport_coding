#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <array>
#define x first
#define y second
using namespace std;
typedef long long ll;
using pii = pair <int, int>;
using vi = vector <int>;
const int N = int(1e6) + 10;
int mp[N], demp[N];
int vis[N], sz[N], W[N];
int idx = 0;
vector < vector <pii> > Adj;
int V, E;


const int maxp = 20;

struct Trie {
	vector<array<int,2>> t;
	Trie() {
		t.assign(1, {-1, -1});
	}
	int query(int x) {
		int ret = 0;
		int d = 0;
		for (int i = maxp-1; i >= 0; i--) {
			ret <<= 1;
			int b = x>>i & 1;
			if (t[d][b ^ 1] == -1) {
				d = t[d][b];
			}
			else {
				d = t[d][b ^ 1];
				ret++;
			}
		}
		return ret;
	}
	void insert(int x) {
		int d = 0;
		for (int i = maxp-1; i >= 0; i--) {
			int b = x>>i & 1;
			if (t[d][b] == -1) {
				t[d][b] = int(t.size());
				t.push_back({-1, -1});
			}
			d = t[d][b];
		}
	}
};

struct Sg {
	int n;
	vector<Trie> t;
	Sg(int n) : n(n) {
		t.resize(2*n);
	}
	pii query(int l, int r, int x) {
		pii ret = pii(0, 0);
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) {
                int tmp = t[l].query(x);
                if (ret.y < tmp) {
                    ret.y = tmp;
                    ret.x = l;
                }
                l++;
            }
			if (r & 1) {
                int tmp = t[r].query(x);
                if (ret.y < tmp) {
                    ret.y = tmp;
                    ret.x = r;
                }
                --r;
            }
		}
		return ret;
	}
	void insert(int i, int x) {
		for (i += n; i > 0; i >>= 1) {
			t[i].insert(x);
		}
	}
};

void dfs (int u, int pr) {
    mp[idx] = u;
    demp[u] = idx;
    ++idx;
    vis[u] = 1;
    sz[u] = 1;
    for (auto vPair : Adj[u]) {
        int v = vPair.x;
        if (v == pr) continue;
        if (!vis[v]) {
            dfs (v, u);
            sz[u] += sz[v];
        }
    }
}

void read() {
    cin.ignore();
	int n, u, v, q, k;
	int w = 1;
	cin >> n >> q;
	V = n, E = n - 1;
    Sg sg(n);
	Adj.assign(V, vector <pii>());

    for (int i = 0; i < n; ++i) {
        cin >> W[i];
    }

	for (int e = 0; e < E; ++e) {
		cin >> u >> v;
		--u, --v;
		Adj[u].emplace_back(pii(v, w));
		Adj[v].emplace_back(pii(u, w)); // undirected
	}

    dfs(0, -1);
	for (int i = 0; i < n; i++) {
		sg.insert(mp[i], W[i]);
	}
	for (int iq = 0; iq < q; iq++) {
		int l, r;
        cin >> u >> k;
        l = mp[u];
        r = mp[u] + sz[u];
		auto ans = sg.query(l, r, k);
		printf("%d %d\n", demp[ans.x], ans.y);
	}
}

signed main() {
    read();

	return EXIT_SUCCESS;
}
