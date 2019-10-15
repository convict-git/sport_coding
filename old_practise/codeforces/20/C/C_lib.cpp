#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
using namespace std;

const int maxn = 1e5 + 10;
const long long inf = (long long) 1e18;
vector < vector <pair <int, int> > >Adj;
int n, m;

vector <long long> dist;

class Compare  {
   public:
      inline bool operator () (const int &u, const int &v) const {
         return dist[u] > dist[v];
      }
};

void dijkstra (int src, int target) {
   vector <bool> vis(n, false);
   vector <int> pathRecover(n);
   dist.assign(n, inf);
   dist[src] = 0;
   priority_queue < int, vector <int>, Compare> Q;

   Q.push(src);

   while (!Q.empty()) {
      int u = Q.top();
      Q.pop();
      if (vis[u]) continue;
      vis[u] = true;

      for (auto vPair : Adj[u]) {
         int v = vPair.second;
         int w = vPair.first;

         if (!vis[v] && dist[v] > dist[u] + w) {
            dist[v] = dist[u] + 1ll*w;
            pathRecover[v] = u;
            Q.push(v);
         }
      }
   }
   if (dist[target] == inf)
      cout << -1 << '\n';
   else {
      vector <int> Path;
      int v = target;
      while (true) {
         Path.push_back(v);
         if (v == src) break;
         v = pathRecover[v];
      }
      reverse(Path.begin(), Path.end());
      for_each(Path.begin(), Path.end(), [&] (const int &v)->void { cout << v + 1 << ' '; });
      cout << '\n';
   }
}

/*
const int N = int(1e5) + 10;
int Par[N];

bool spfa (int src, int target) {
   vector <int> inQueue (n, false);
   int cnt[N] = {0};
   dist.assign(N, inf);
   for (int i = 0; i < N; ++i)
      Par[i] = -1;

   queue <int> Q;
   Q.push(src);
   dist[src] = 0;
   inQueue[src] = true;

   while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      inQueue[u] = false;

      for (auto vPair : Adj[u]) {
         int v = vPair.second;
         long long w = vPair.first;
         if (dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            Par[v] = u;
            if (!inQueue[v]) {
               Q.push(v);
               inQueue[v] = true;
               ++cnt[v];
               assert (cnt[v] < n);
            }
         }
      }
   }

   if (dist[target] == inf)
      cout << -1 << '\n';
   else {
      vector <int> Path;
      int v = target;
      while (true) {
         Path.push_back(v);
         if (v == src) break;
         v = Par[v];
      }
      reverse(Path.begin(), Path.end());
      for_each(Path.begin(), Path.end(), [&] (const int &v)->void { cout << v + 1 << ' '; });
      cout << '\n';
   }
   return true;
}
*/
/*

void dijkstra_pq (int src, int target) {
	vector <long long> dist (n, inf);
	vector <bool> vis (n, false);
	vector <int> pathRecover(n);

	dist[src] = 0;

	using plli = pair <long long, int>;
	priority_queue < plli, vector <plli>, greater <plli> > Q;

	for (int i = 0; i < n; ++i) {
		Q.push ({dist[i], i});
	}

	while (!Q.empty()) {
		int u = Q.top().second;
		Q.pop();
		if (vis[u]) continue;
		vis[u] = true;

		for (auto ver : Adj[u]) {
			int v = ver.second;
			int w = ver.first;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pathRecover[v] = u;
				Q.push ({dist[v], v});
			}
		}
	}
	if (dist[target] == inf) {
		cout << -1 << '\n';
	}
	else {
		vector <int> pth;
		pth.push_back (target);
		int tmp = target;
		while (tmp != src) {
			tmp = pathRecover[tmp];
			pth.push_back (tmp);
		}
		reverse (pth.begin(), pth.end());
		for_each (pth.begin(), pth.end(), [] (int v) { cout << v + 1 << ' '; });
		cout << '\n';
	}
}
*/

/*
void dijkstra (int src, int target) {
	vector <long long> dist (n, inf);
	vector <int> pathRecover (n);
	dist[src] = 0;
	set < pair<long long, int> > Q;
	for (int i = 0; i < (int) dist.size(); ++i) {
		Q.insert ({dist[i], i});
	}
	while (!Q.empty()) {
		int u = Q.begin()->second;
		long long len = Q.begin()->first;
		if (len == inf || u == target) break;
		Q.erase (Q.begin());
		for (auto Ver : Adj[u]) {
			int v = Ver.second;
			int w = Ver.first;
			if (dist[v] > dist[u] + w) {
				dist[v] = dist[u] + w;
				pathRecover[v] = u;
				Q.insert ({dist[v], v});
			}
		}
	}
	if (dist[target] == inf) cout << -1 << '\n';
	else {
		vector <int> pth;
		pth.push_back (target);
		int tmp = target;
		while (tmp != src) {
			tmp = pathRecover[tmp];
			pth.push_back (tmp);
		}
		reverse (pth.begin(), pth.end());
		for_each (pth.begin(), pth.end(), [] (int v) { cout << v + 1 << ' '; });
		cout << '\n';
	}
}
*/

int main() {
	IOS; PREC;

	cin >> n >> m;
	Adj.resize (n);

	for (int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		if (u == v) continue;
		Adj[u].push_back ({w, v});
		Adj[v].push_back ({w, u});
	}

	dijkstra (0, n - 1);

	return EXIT_SUCCESS;
}

