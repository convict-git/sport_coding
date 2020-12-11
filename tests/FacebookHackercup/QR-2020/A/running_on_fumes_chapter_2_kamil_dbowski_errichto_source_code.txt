#include <bits/stdc++.h>
using namespace std;
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
	*this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
// debug & operator << (debug & dd, P p) { dd << "(" << p.x << ", " << p.y << ")"; return dd; }

// const int INF = 1e9 + 5;
const long long LONG_INF = 1e18L + 5;

struct Centroid {
	map<int,int> distance;
	vector<pair<int,int>> sorted;
};

struct TestCase {
	vector<vector<int>> edges;
	vector<long long> cost;
	vector<int> subtree;
	vector<bool> forbidden;
	vector<Centroid> centroids;
	vector<vector<int>> belongs;
	void dfs_sizes(int a, int par) {
		subtree[a] = 1;
		for(int b : edges[a]) {
			if(!forbidden[b] && b != par) {
				dfs_sizes(b, a);
				subtree[a] += subtree[b];
			}
		}
	}
	void dfs_centroid(int a) {
		dfs_sizes(a, -1);
		int cc = subtree[a];
		while(true) {
			bool moved = false;
			for(int b : edges[a]) {
				if(!forbidden[b] && 2 * subtree[b] >= cc && subtree[b] < subtree[a]) {
					a = b;
					moved = true;
					break;
				}
			}
			if(!moved) {
				break;
			}
		}
		map<int,int> distance;
		vector<pair<int,int>> q;
		q.emplace_back(0, a);
		distance[a] = 0;
		for(int i = 0; i < (int) q.size(); ++i) {
			int me = q[i].second;
			for(int b : edges[me]) {
				if(!forbidden[b] && !distance.count(b)) {
					int d2 = q[i].first + 1;
					distance[b] = d2;
					q.emplace_back(d2, b);
				}
			}
		}
		reverse(q.begin(), q.end()); // from big to small
		Centroid cen{distance, q};
		int nxt = centroids.size();
		centroids.push_back(cen);
		for(pair<int,int> p : q) {
			int me = p.second;
			assert(distance.count(me));
			belongs[me].push_back(nxt);
		}
		forbidden[a] = true;
		for(int b : edges[a]) {
			if(!forbidden[b]) {
				dfs_centroid(b);
			}
		}
	}
	void test_case() {
		int n, range, start, end;
		scanf("%d%d%d%d", &n, &range, &start, &end);
		--start;
		--end;
		// debug() << imie(n) imie(range) imie(start) imie(end);
		edges.resize(n);
		cost.resize(n);
		subtree.resize(n);
		forbidden.resize(n);
		belongs.resize(n);
		for(int i = 0; i < n; ++i) {
			int par;
			scanf("%d%lld", &par, &cost[i]);
			if(cost[i] == 0) {
				cost[i] = LONG_INF;
			}
			if(par != 0) {
				par--;
				edges[i].push_back(par);
				edges[par].push_back(i);
			}
		}
		dfs_centroid(0);
		vector<long long> dp(n, LONG_INF);
		dp[start] = 0;
		vector<bool> done(n);
		long long answer = LONG_INF;
		set<pair<long long, int>> q;
		q.insert({dp[start], start});
		while(!q.empty()) {
			auto it = q.begin();
			int v = it->second;
			q.erase(it);
			if(done[v]) {
				continue;
			}
			done[v] = true;
			if(dp[v] >= LONG_INF) {
				break;
			}
			for(int c_id : belongs[v]) {
				Centroid& c = centroids[c_id];
				assert(c.distance.count(v));
				int remaining = range - c.distance[v];
				if(remaining >= 0) {
					while(!c.sorted.empty() && c.sorted.back().first <= remaining) {
						int who = c.sorted.back().second;
						c.sorted.pop_back();
						if(who == end) {
							answer = min(answer, dp[v]);
						}
						else if(dp[v] + cost[who] < dp[who]) {
							q.erase({dp[who], who});
							dp[who] = dp[v] + cost[who];
							q.insert({dp[who], who});
						}
						/*
							debug() << imie(c_id) imie(p);
							if(p.first == end) {
								answer = min(answer, dp[v]);
							}
							else {
								dp[p.first] = min(dp[p.first], dp[v] + cost[p.first]);
								q.insert({dp[p.first], p.first});
							}
						}*/
					}
				}
			}
		}
		if(answer >= LONG_INF) {
			puts("-1");
		}
		else {
			printf("%lld\n", answer);
		}
		// debug() << imie(dp);
		// printf("%lld\n", dp[end] - cost[end]);
	}
};

int main() {
	int T;
	scanf("%d", &T);
	for(int nr = 1; nr <= T; ++nr) {
		cerr << nr << " ";
		printf("Case #%d: ", nr);
		TestCase o;
		o.test_case();
	}
}
