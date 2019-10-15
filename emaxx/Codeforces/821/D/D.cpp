#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#include         <ext/pb_ds/assoc_container.hpp>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second

template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;
using namespace __gnu_pbds;
using pii = pair <int, int>;

const int infi = (int) 1e9;
const int N = (int)1e4 + 10;
int n, m, k, V, f = 0;
vector < vector <pii> > Adj;
vector <pii> inp;
struct chash { int operator()(pii p) const { return p.x*31 + p.y; } }; gp_hash_table <pii, int, chash> mp;

bool comp (const pii& p1, const pii& p2) { return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y); }
bool sameRC(const pii& p1, const pii& p2) { return p1.x == p2.x || p1.y == p2.y; }
bool nxtRC(const pii& p1, const pii& p2) { return p1.x + 1 == p2.x || p1.y + 1 == p2.y; }
bool inside(const pii& p1, const pii& p2) { return p1.x <= p2.x && p1.y <= p2.y; }

struct state{
	static int ans;
	pii u, lit;
	int wt, d;
	state(pii _u, pii _l, int _wt, int _d)
		: u(_u), lit(_l), wt(_wt), d(_d) {}

	state nextMove (pii nxt) {
		if (!sameRC(u, nxt) && nxtRC(u, nxt)) {
			if (lit.x == nxt.x - 1 || lit.y == nxt.y - 1)
				return {nxt, {-2, -2}, 0, d};
			else
				return {nxt, {-2, -2}, 1, d + 1};
		}
		else if (sameRC(u, nxt)) {
			if (lit.x == nxt.x || lit.y == nxt.y)
				return {nxt, lit, 0, d};

			else {
				if (u.x + 1 == nxt.x || u.y + 1 == nxt.y)
					return {nxt, {-2, -2}, 0, d};
				else {
					int _tmpx = (u.x == nxt.x ? u.x : -2),
						_tmpy = (u.y == nxt.y ? u.y : -2);
					return {nxt, {_tmpx, _tmpy}, 1, d + 1};
				}
			}
		}
		else assert (false); //some error in edgePreProcess
	}

	static bool isAns (const state& s) {
		if (s.u.x == n - 1 || s.u.y == m - 1) {
			if (s.lit == pii(n - 1, -2) || s.lit == pii(-2, m - 1))
				nix(ans, s.d);
			else nix(ans, s.d + 1);
			return true;
		}
		else if (s.u.x == n - 2 && s.u.y == m - 2) {
			if (s.lit != pii(-2, -2)) nix(ans, s.d);
			else nix(ans, s.d + 1);
			return true;
		}
		else return false;
	}

	void show() {
		int cx = u.x, cy = u.y;
		set <pii> St;
		for (int i = 0; i < V; ++i)
			St.insert(inp[i]);
		system("sleep 2 && clear");

		for (int i = 0; i < n; ++i) {
			string st = "";
			for (int j = 0; j < m; ++j) {
				if (i == cx && j == cy) st += "\033[44m  \033[0m";
				else if (St.find(pii(i, j)) != St.end()) st += "\033[41m  \033[0m";
				else st += "\033[42m  \033[0m";
			}
			cout << st << '\n';
		}
		cerr << u.x << ' ' << u.y << " Llit " << lit.x << ' ' << lit.y << ' ' << "dist " << d << '\n';
	}
};

int state::ans = infi;

void edgePreProcess() {
	for (int u = 0; u < V; ++u) {
		if (inp[u] == pii(n - 1, m - 1)) f = 1;
		mp[inp[u]] = u;
		for (int v = u + 1; v < V; ++v) {
			if (inside(inp[u], inp[v])) {
				if (sameRC(inp[u], inp[v]) || nxtRC(inp[u], inp[v])) {
					Adj[u].push_back(inp[v]);
				}
				else break;
			}
		}
	}
	/*
	   for (int u = 0; u < V; ++u) {
//cerr << inp[u].x << ' ' << inp[u].y << ':';
int idxu = mp[inp[u]];
for(auto v : Adj[idxu]) {
//cerr << '(' << v.x << ',' << v.y << ' ' << ')' << ' ';
}
//cerr << '\n';
}
*/
}


void bfs (pii src, pii tar) {
	vector <int> dist(V + 1, infi);
	deque <state> Q;
	dist[mp[src]] = 0;
	if (f == 0) mp[tar] = V;

	Q.push_back(state(src, {-2, -2}, 0, 0));

	while (!Q.empty()) {
		state s = Q.front();
		state::isAns(s);
		s.show();
		int idxu = mp[s.u];
		Q.pop_front();
		for (auto v : Adj[idxu]) {
			int idxv = mp[v];
			state vSt = s.nextMove(v);
			if (dist[idxv] > dist[idxu] + vSt.wt) {
				if (vSt.wt == 0) Q.push_front(vSt);
				if (vSt.wt == 1) Q.push_back(vSt);
				dist[idxv] = dist[idxu] + vSt.wt;
			}
		}
	}
	nix (state::ans, dist[mp[tar]]);
	if (state::ans == infi) state::ans = -1;
}

void read() {
	cin >> n >> m >> k;
	V = k;
	Adj.assign(V, vector <pii>());
	int x, y;
	for (int v = 0; v < k; ++v) {
		cin >> x >> y;
		--x, --y;
		inp.push_back({x, y});
	}
	sort (inp.begin(), inp.end(), comp);
}
void check () {
	state s1 = {{2, 1}, {-2, -2}, 0, 0};
	pii p = {2, 3};
	state s = s1.nextMove(p);
	cout << s.u.x << ' ' << s.u.y << ' ' << s.lit.x << ' ' << s.lit.y << ' ' << s.d << '\n';

}

int main() {
	IOS; PREC;
	read();
	edgePreProcess();
	bfs(pii(0, 0), pii(n - 1, m - 1));
	cout << state::ans << '\n';
	check();
	return EXIT_SUCCESS;
}
