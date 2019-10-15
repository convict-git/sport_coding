#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (2); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ] "
#define x        first
#define y        second
using ll = long long;
using ld = long double;
using pii = pair<int,int>;

#define debug(args...) { \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) { it->empty();
   cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << fixed << setprecision(10) << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

const int N = 13, M = 55;
const ld inf = 1e18, eps = 1e-9;
ld dp[N][1 << N], wgt[N][N], W[M][M];
int par[N][1 << N], start[N][1 << N], cd[N];
ld price[N];
int n, nc, m;

ld tsp() {
   for (int mask = 0; mask < (1 << n); ++mask)
      for (int i = 0; i < n; ++i)
         dp[i][mask] = inf;

   for (int i = 0; i < n; ++i)
      dp[i][1 << i] = 0, par[i][1 << i] = -1, start[i][1 << i] = i;

   for (int mask = 1; mask < (1 << n); ++mask) {
      for (int pos = 0; pos < n; ++pos)
      {
         if (!(mask & (1 << pos))) continue;
         ld mn_val = inf;
         for (int prv = 0; prv < n; ++prv) {
            if (pos == prv || !(mask & (1 << prv)))
               continue;
            ld guess = dp[prv][mask-(1<<pos)] + wgt[prv][pos];
            if (mn_val + eps > guess) {
               mn_val = guess;
               par[pos][mask] = prv;
               start[pos][mask] = start[prv][mask-(1 << pos)];
            }
         }
         dp[pos][mask] = min(dp[pos][mask], mn_val);
      }
   }

   ld mn_cycle = inf;
   int pos = -1, mask = (1 << n) - 1;
   for (int i = 0; i < n; ++i) {
      ld go = dp[i][mask] + wgt[i][start[i][mask]];
      if (mn_cycle + eps > go) {
         mn_cycle = go;
         pos = i;
      }
   }

   vector <int> cycle;
   while (pos != -1) {
      cycle.push_back(pos);
      int tmp = pos;
      pos = par[pos][mask];
      mask -= (1 << tmp);
   }
   // for (int v : cycle) { cerr << v << ' '; } cerr << '\n';

   return mn_cycle;
}

void solve() {
   for (int k = 0; k < nc; ++k)
      for (int i = 0; i < nc; ++i) for (int j = 0; j < nc; ++j)
            W[i][j] = W[j][i] = min(W[i][j], W[i][k] + W[k][j]);


   for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
      wgt[i][j] = W[cd[i]][cd[j]];

   ld total_tour_cost = tsp();
   ld mx_saving = 0;

   for (int mask = 1; mask < (1 << n); ++mask) {
      if (!(mask & 1)) continue; // should contain home

      ld min_tour_cost = inf;
      ld saving = 0;

      for (int i = 0; i < n; ++i) {
         if (mask & (1 << i)) {
            saving += price[i];

            ld go = dp[i][mask] + wgt[i][start[i][mask]];
            min_tour_cost = min(min_tour_cost, go);
         }
      }
      if (saving + eps > min_tour_cost)
         mx_saving = max(mx_saving, saving - min_tour_cost);
   }

   if (fabs(mx_saving - 0) < eps) {
      cout << "Don't leave the house\n";
   }
   else {
      cout << "Daniel can save $" << mx_saving << '\n';
   }
}

void read() {
   cin >> nc >> m;
   ++nc;
   for (int i = 0; i < nc; ++i) for (int j = 0; j < nc; ++j)
      W[i][j] = inf;

   for (int e = 0; e < m; ++e) {
      int u, v;
      ld wt;
      cin >> u >> v >> wt;
      W[u][v] = W[v][u] = min(W[u][v], wt);
   }

   cin >> n;
   ++n;

   cd[0] = 0, price[0] = 0;
   for (int i = 1; i < n; ++i) {
      cin >> cd[i] >> price[i];
   }
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   while (tc--) read(), solve();

   return EXIT_SUCCESS;
}
