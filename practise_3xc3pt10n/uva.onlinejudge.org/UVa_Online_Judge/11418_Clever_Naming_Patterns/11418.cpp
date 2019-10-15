#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    "[ " << #x << " : " << x << " ]"
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;

const int N = 26 * 26 + 26 + 2 + 100;
const int infi = (int)1e9;

int f[N][N];
vector < vector <int> > Adj;
int np;
int n, m;
int Par[N];
map <string, int> mp;
map <int, string> dmp;

int bfs (int s, int t) {
   fill (Par, Par + N, -1);
   Par[s] = -2;

   queue <pii> Q;
   Q.push(pii(s, infi));

   while (!Q.empty()) {
      pii tmp = Q.front();
      Q.pop();
      int u = tmp.x, flow = tmp.y;

      for (int v : Adj[u]) {
         if (Par[v] == -1 && f[u][v]) {
            Par[v] = u;
            int newFlow = min(flow, f[u][v]);
            if (v == t) {
               return newFlow;
            }
            Q.push(pii(v, newFlow));
         }
      }
   }
   return 0;
}

int edmondsKarp(int s, int t) {
   int flow = 0;
   int newFlow;

   while ((newFlow = bfs (s, t))) {
      flow += newFlow;
      int cur = t;
      while (cur != s) {
         int prv = Par[cur];
         f[prv][cur] -= newFlow;
         f[cur][prv] += newFlow;
         cur = prv;
      }
   }
   return flow;
}

inline void addEdges (int u, int v, int flow) {
   Adj[u].push_back(v);
   Adj[v].push_back(u);
   f[u][v] = flow;
}

string correction(string name) {
   for (int i = 0; i < (int)name.size(); ++i) {
      if (i == 0 && name[i] - 'a' >= 0 && name[i] - 'z' <= 0)
         name[i] = char(name[i] - 'a' + 'A');
      else if (i != 0 && name[i] - 'A' >= 0 && name[i] - 'Z' <= 0)
         name[i] = char(name[i] - 'A' + 'a');
   }
   return name;
}

void solve(int tc) {
   mp.clear();
   dmp.clear();

   for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
         f[i][j] = 0;

   cin >> np;
   Adj.assign(N, vector <int> ());
   int s = N - 2, t = N - 1;
   const int alpha = N - 2 - 26;
   int k, strIdx = 26;
   string st;
   vector <vector <string> >input(26, vector <string>());
   set <string> PossibleNames;


   for (int i = 0; i < np; ++i) {
      cin >> k;
      while (k--) {
         cin >> st;
         st = correction(st);
         input[i].push_back(st);
         PossibleNames.insert(st);
      }
   }

   for (int i = alpha; i < alpha + 26; ++i) {
      addEdges(i, t, 1);
   }

   for (string name : PossibleNames) {
      mp[name] = strIdx;
      dmp[strIdx] = name;
      int v = alpha + name[0] - 'A';
      addEdges(strIdx, v, 1);
      ++strIdx;
   }

   for (int i = 0; i < np; ++i) {
      addEdges(s, i, 1);

      for (string name : input[i]) {
         int v = mp[name];
         addEdges(i, v, 1);
      }
   }
   int flow = edmondsKarp(s, t);
   assert(flow == np);

   cout << "Case #" << tc << ":\n";
   for (int i = alpha; i < alpha + 26; ++i) {
      for (int v : Adj[i]) {
         if (v == t) continue;
         if (f[i][v] == 1) {
            cout << dmp[v] << '\n';
            break;
         }
      }
   }
   cout.flush();
}

signed main() {
   int tc;
   cin >> tc;
   for (int i = 1; i <= tc; ++i) {
      solve(i);
   }
   return EXIT_SUCCESS;
}

