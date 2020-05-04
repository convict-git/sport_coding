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

const int N = 510 + 110 + 2;
const int infi = (int)1e9;

int f[N][N];
vector < vector <int> > Adj;
vector <pii> interval;
int n, m, nm, capPlace, totalWater;
int Par[N];

struct Trip {
   int v, a, b;
   inline bool operator < (const Trip& o) const {
      return a < o.a || (a == o.a && b > o.b);
   }
};

vector <Trip> triplets;

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

void solve(int tc) {
   totalWater = 0;
   int s = N - 2, t = N - 1;
   Adj.assign(N, vector <int> ());
   triplets.clear();
   interval.clear();
   int v, a, b;
   set <int> tmw;

   for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
         f[i][j] = 0;

   for (int i = 0; i < nm; ++i) {
      cin >> v >> a >> b;
      --b;
      totalWater += v;
      triplets.push_back({v, a, b});
      tmw.insert(a); tmw.insert(b);

      Adj[s].push_back(i);
      Adj[i].push_back(s);
      f[s][i] = v;
   }

   for (set <int> ::iterator it = tmw.begin(); it != tmw.end(); ++it) {
      if (it == tmw.begin()) {
         a = *it;
         interval.push_back({a, a});
         continue;
      }
      b = *it;
      if (b - a - 1 > 0) interval.push_back({a + 1, b - 1});
      interval.push_back({b, b});
      a = b;
   }


   for (int i = 0; i < (int)interval.size(); ++i) {
      a = interval[i].x, b = interval[i].y;

      Adj[i + nm].push_back(t);
      Adj[t].push_back(i + nm);
      f[i + nm][t] = (b - a + 1) * capPlace;

      for (int j = 0; j < nm; ++j) {
         if (triplets[j].a <= a && triplets[j].b >= b) {
            Adj[j].push_back(i + nm);
            Adj[i + nm].push_back(j);
            f[j][i + nm] = infi;
         }
      }

   }

   cout << "Case " << tc << ": ";
   int flow = edmondsKarp(s, t);
   if (flow == totalWater) {

      cout << "Yes\n";
      vector <pii> prep, ans;
      for (int i = 0; i < nm; ++i) {
         prep.clear(), ans.clear();
         for (int v : Adj[i]) {
            if (v == s) continue;
            if (f[v][i]) {
               prep.push_back(pii(interval[v - nm].x, interval[v - nm].y + 1));
            }
         }

         int aa = prep[0].x, bb = prep[0].y;
         for (int j = 1; j < (int)prep.size(); ++j) {
            if (bb == prep[j].x)
               bb = prep[j].y;
            else {
               ans.push_back(pii(aa, bb));
               aa = prep[j].x, bb = prep[j].y;
            }
         }
         ans.push_back(pii(aa, bb));


         int sz = (int) ans.size();
         cout << sz << ' ';
         for (int j = 0; j < sz; ++j) {
            cout << '(' << ans[j].x << ',' << ans[j].y << ')' << ' ';
         }
         cout << '\n';
      }
   }
   else cout << "No\n";

}

signed main() {
   int tc = 1;
   while (cin >> nm >> capPlace, nm) {
      solve(tc);
      ++tc;
   }

   return EXIT_SUCCESS;
}

