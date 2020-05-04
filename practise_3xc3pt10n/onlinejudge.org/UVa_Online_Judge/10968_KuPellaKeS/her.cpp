#include <bits/stdc++.h>
using namespace std;
vector <vector<int>> adj;
vector <int> deg;
vector <int> parent;

void bfs(int u, int f) {
  parent[u] = u;
  queue <int> q;
  q.push(u);
  while (!q.empty()) {
  	int x = q.front();
  	q.pop();
  	for (vector<int>::iterator it = adj[x].begin(); it != adj[x].end(); it++) {
  		if (parent[*it] == -1) { // unvisited
  			parent[*it] = x;
  			if (*it == f)
  				return;
  			q.push(*it);
  		}
  	}
  }
 return;
}

int deg_check(int n, int *x, int *y) {
 bool first = true;
 for (int i = 0; i < n; i++) {
 	if (deg[i] < 2)
 		return 0;
 	else if (deg[i] % 2 == 1 && first == true)
 		*x = i, first = false;
 	else if (deg[i] % 2 == 1 && first == false)
 		*y = i;
 }
 if (first == true)
 	return 2; // indicating fully even; possible!
 else return 1;
}

int main () {
int n, m, x, y, ans = -1;
int u, v;
bool okay = true;
scanf(" %d %d", &n, &m);
do {
  ans = -1;
  adj.resize(n);
  deg.resize(n);
  parent.resize(n);
  u = -1, v = -1;
  for (int i = 0; i < n; i++) {
  	parent[i] = -1;
  	deg[i] = 0;
  	adj[i].push_back(i);
  }
  for (int i = 0; i < m; i++) {
  	scanf(" %d %d", &x, &y);
  	adj[x - 1].push_back(y - 1);
  	adj[y - 1].push_back(x - 1);
  	deg[x - 1]++;
  	deg[y - 1]++;
  }
  //getchar();
  ans = deg_check(n, &u, &v);
  if (ans == 0)
  	printf("Poor Koorosh\n");
  else if (ans == 2)
  	printf("0\n");
  else {
  	bfs(u, v);
  	int ecount = 0;
  	int curr = parent[v];
  	while (curr != u) {
		if (deg[curr] < 4) {
			printf("Poor Koorosh\n");
			okay = false;
			break;
		}
		else {
			ecount++;
			curr = parent[curr];
		}
	}
	 if (okay == true)
  		printf("%d\n", ecount + 1);
  }
  scanf(" %d %d", &n, &m);
  adj.clear();
  parent.clear();
  deg.clear();
  okay = true;
} while (!(n == 0 && m == 0));
 return 0;
}
