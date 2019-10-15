#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
const int N = (int)1e6 + 10;
int n, m, k;
int rep[N], rnk[N], sz[N], paint[N];
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
vector <string> C;

void makeSet() {
   for(int u = 0; u < n * m; ++u)
      rep[u] = u, rnk[u] = 0, sz[u] =  1, paint[u] = 0;
}

int findSet(int u) {
   int ru = u;
   while (ru != rep[ru])
      ru = rep[ru];

   while (u != rep[u]) {
      int tmp = rep[u];
      rep[u] = ru;
      u = tmp;
   }
   return ru;
}

void mergeSet(int u, int v) {
   int ru = findSet(u), rv = findSet(v);
   if (rnk[ru] > rnk[rv]) {
      rep[rv] = rep[ru];
      sz[ru] += sz[rv];
   }
   else {
      rep[ru] = rep[rv];
      sz[rv] += sz[ru];
   }

   if (rnk[ru] == rnk[rv]) {
      ++rnk[rv];
   }
}

inline bool isValid (int xx, int yy, char c) {
   return xx >= 0 && yy >= 0 && xx < n && yy < m && C[xx][yy] == c;
}

void dfs (int ux, int uy, bool vis[], char c) {
   vis[m * ux + uy] = true;
   for (int dir = 0; dir < 4; ++dir) {
      int xx = ux + dx[dir], yy = uy + dy[dir];

      if (isValid (xx, yy, c) && !vis[m * xx + yy]) {
         dfs (xx, yy, vis, c);
         mergeSet(m * xx + yy, m * ux + uy);
      }
   }
}

void solve() {
   makeSet();
   bool vis[N];
   for (int i = 0; i < n * m; ++i) vis[i] = 0;


   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
         if (C[i][j] == '.' && !vis[m * i + j])
            dfs (i, j, vis, '.');
      }
   }

   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
         if (C[i][j] == '*') {
            for (int dir = 0; dir < 4; ++dir) {
               int xx = i + dx[dir], yy = j + dy[dir];
               if (isValid(xx, yy, '.')) {
                  int ru = findSet(m * xx + yy);
                  paint[ru] += 1;
               }
            }
         }
      }
   }

   int u, v;
   while (k--) {
      cin >> u >> v;
      --u, --v;
      cout << paint[findSet(m * u + v)] << '\n';
   }
}
void read() {
   string S;
   getchar();
   for (int i = 0; i < n; ++i) {
      getline(cin, S);
      cerr << S << '\n';
      C.push_back(S);
   }

}

signed main() {
   C.clear();
   cin >> n >> m >> k;
   read();
   solve();
   return EXIT_SUCCESS;
}
