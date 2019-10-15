#include <bits/stdc++.h>
using namespace std;
#define infi 1e7
vector<vector<int> > adj;
vector<int> dist;
vector<int> visited;

int n;

int bfs(int s) {
   queue<int> q;
   int u;
   visited.assign(n, 0);
   dist.assign(n, infi);
   dist[s] = 0;
   q.push(s);
   while (!q.empty()) {
      u = q.front();
      q.pop();
      for (vector<int>::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
         if (visited[*it] == 0) {
            dist[*it] = 1 + dist[u];
            visited[*it] = 1;
            q.push(*it);
         }
         if (*it == s)
            return dist[s];
      }
   }
   return -1;
}

void solve() {
   int ans = 0;
   for (int i = 0; i < n; i++) {
      ans = bfs(i);
      if (ans == -1)
         printf("NO WAY\n");
      else
         printf("%d\n", ans);
   }
   return;
}

int main () {
   int t = 0;
   scanf(" %d ", &n);
   adj.assign(n, {});
   for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
         scanf("	%d", &t);
         if (t == 1)
            adj[i].push_back(j);
      }
   }
   solve();
   return 0;
}
