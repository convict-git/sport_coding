#include <bits/stdc++.h>
using namespace std;

const int OFFST = 65;
struct edge {
	int u, v, w;
};

bool compare (const edge& e1, const edge& e2) {
   return (e1.w < e2.w || (e1.w == e2.w && e1.u < e2.u) || (e1.w == e2.w && e1.u == e2.u && e1.v < e2.v));
}

int n;
vector <edge> Edges;

vector <int> parent, Rank;

vector <edge> T;

void make_set () {
	for (int i = 0; i < n; i++)
		parent[i] = i;
	return;
}

int find_set (int u) {
	while (u != parent[u])
		u = parent[u];
	return u;
}

void merge_set (int u, int v) {
	int root_u = find_set(u);
	int root_v = find_set(v);
	if (root_u == root_v)
		return;
	if (Rank[root_u] > Rank[root_v]) // u higher
		parent[root_v] = root_u;
	else if (Rank[root_v] > Rank[root_u]) // v higher
		parent[root_u] = root_v;
	else {
		parent[root_v] = root_u;
		Rank[root_u]++;
	}
	return;
}

void kruskal () {
	parent.assign(n, 0);
	Rank.assign(n, 0);
	make_set();
	sort(Edges.begin(), Edges.end(), compare);
	int u, v, w;
	for (auto e : Edges) {
		u = e.u;
		v = e.v;
		w = e.w;
		if (find_set(u) == find_set(v))
			continue;
		merge_set(u, v);
		T.push_back({u, v, w});
	}
	return;
}

void solve () {
	kruskal();
	int u, v, w;
	sort(T.begin(), T.end(), compare);
	for (auto e : T) {
		u = e.u;
		v = e.v;
		w = e.w;
		cout << (char)(u + OFFST) << "-" << (char)(v + OFFST) << " " << w << '\n';
	}
	T.clear();
	Edges.clear();
	return;
}

void read () {
	cin >> n;
	char ch;
	int w;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> w;
			scanf("%c", &ch);
			if (!w)
				continue;
			Edges.push_back({min(i, j), max(i, j), w});
		}
	}
	return;
}

int main () {
	int tst = 1;
	int tot;
	cin >> tot;
	while (tot--) {
		read();
      cout << "Case " << tst << ":" << '\n';
		solve();
		tst++;
	}
	return 0;
}
