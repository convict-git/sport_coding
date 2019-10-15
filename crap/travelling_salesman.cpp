#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
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
	cerr << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

const int N = 17;
const ll inf = (ll) 1e18;
ll dp[N][1 << N];
int par[N][1 << N], start[N][1 << N], wgt[N][N];
int n;

ll tsp() {
//    for (int k = 0; k < n; ++k)    //Floyd-Warshall for shortest dist wgts (undirected)
//       for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j)
//          wgt[j][i] = wgt[i][j] = min(wgt[i][j], wgt[i][k] + wgt[k][j]);

   for (int mask = 0; mask < (1 << n); ++mask)
      for (int i = 0; i < n; ++i)
         dp[i][mask] = inf;

   for (int i = 0; i < n; ++i)
      dp[i][1 << i] = 0, par[i][1 << i] = -1, start[i][1 << i] = i;

   for (int mask = 1; mask < (1 << n); ++mask) {
      for (int pos = 0; pos < n; ++pos)
      {
         if (!(mask & (1 << pos))) continue;
         ll mn_val = inf;
         for (int prv = 0; prv < n; ++prv) {
            if (pos == prv || !(mask & (1 << prv)) || !wgt[prv][pos])
               continue;
            ll guess = dp[prv][mask-(1<<pos)] + wgt[prv][pos];
            if (mn_val > guess) {
               mn_val = guess;
               par[pos][mask] = prv;
               start[pos][mask] = start[prv][mask-(1 << pos)];
            }
         }
         dp[pos][mask] = min(dp[pos][mask], mn_val);
      }
   }

   ll mn_cycle = inf;
   int pos = -1, mask = (1 << n) - 1;
   for (int i = 0; i < n; ++i) {
      ll go = dp[i][mask] + wgt[i][start[i][mask]];
      if (mn_cycle > go) {
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
   for (int v : cycle) { cerr << v << ' '; } cerr << '\n';

   return mn_cycle;
}

signed main() {
   IOS; PREC;

   return EXIT_SUCCESS;
}

