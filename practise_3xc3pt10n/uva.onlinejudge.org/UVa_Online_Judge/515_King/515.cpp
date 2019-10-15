#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;
using pii = pair <int,int>;

const int N = (int)1e2 + 10;
const long long inf = (long long)1e18;

int n, m, V;
vector <vector <pii> > Adj;

bool spfa (int src) {
   bool inQ[N];
   int rel[N];
   long long d[N];
   queue <int> Q;

   for (int i = 0; i < V; ++i)
      inQ[i] = false, d[i] = inf, rel[i] = 0;

   d[src] = 0;
   Q.push(src);
   inQ[src] = true;

   while (!Q.empty()) {
      int u = Q.front();
      Q.pop();
      inQ[u] = false;

      for (auto vPair : Adj[u]) {
         int v = vPair.x;
         long long w = vPair.y;

         if (d[u] != inf && d[v] > d[u] + w) {
            d[v] = d[u] + w;
            ++rel[v];

            // edge cannot be relaxed more than v times (hence negative wgt cycle)
            if (rel[v] > V) return false;
            if (!inQ[v]) {
               Q.push(v);
               inQ[v] = true;
            }
         }
      }
   }
   return true;
}

void read() {
   int u, v;
   long long w;
   while (cin >> n, n) {
      cin >> m;
      V = n + 2;

      Adj.assign(V, vector <pii> ());
      int si, ni;
      long long ki;
      string oi;

      for (int i = 0; i < n + 1; ++i)
         Adj[n + 1].push_back(pii(i, 0));

      for (int i = 0; i < m; ++i) {
         cin >> si >> ni >> oi >> ki;
         if (oi == "lt")
            u = si - 1, v = si + ni, w = ki - 1;
         else if (oi == "gt")
            u = si + ni, v = si - 1, w = -1*ki - 1;
         else assert (false);

         Adj[u].push_back(pii(v, w));
      }
      if (spfa(n + 1)) cout << "lamentable kingdom\n";
      else cout << "successful conspiracy\n";
   }
}

signed main() {
   IOS; PREC;
   read();

   return EXIT_SUCCESS;
}

