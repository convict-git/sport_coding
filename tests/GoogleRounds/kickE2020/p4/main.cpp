#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don't practice until you get it right. Practice until you can't get it wrong

typedef long long ll;

const ll Maxn = 600;
const ll LIMIT = 1e12;
ll N, M, S, R;
vector <ll> g[Maxn];
vector <ll> store[Maxn];
vector <vector <ll>> rec[Maxn];
vector <ll> availPos[Maxn];
ll shortestDist[Maxn];
ll cost[Maxn][Maxn];

void preproc()
{
}

void reset() {
   // resetting
   for (ll i = 0; i < N; ++i) {
      g[i].clear();
      store[i].clear();
      rec[i].clear();
      availPos[i].clear();
      for (ll j = 0; j < N; ++j) {
         cost[i][j] = LIMIT;
      }
   }
}


void solve()
{

   cin >> N >> M;

   // input
   cin >> N >> M >> S >> R;
   reset();
   // graph
   for (ll i = 0; i < M; ++i) {
      ll u, v;
      cin >> u >> v; --u, --v;
      g[u].push_back(v);
      g[v].push_back(u);
   }

   // store
   for (ll i = 0; i < N; ++i) {
      ll Ci; cin >> Ci;
      while (Ci--) {
         ll type; cin >> type; --type;
         store[i].push_back(type);
         availPos[type].push_back(i);
      }
   }

   //  recipes
   for (ll i = 0; i < R; ++i) {
      ll Ki; cin >> Ki;
      set <ll> tmpSet;
      while (Ki--) {
         ll type; cin >> type; --type;
         tmpSet.insert(type);
      }
      ll B; cin >> B; --B;
      rec[B].push_back(vector <ll> ());
      for (ll s : tmpSet) {
         rec[B].back().push_back(s);
      }
   }

   ll res = LIMIT;
   // final solution
   for (ll pos = 0; pos < N; ++pos) { // final pos of stones
      // create shortestDist [s] array on pos for the graph
      for (ll i = 0; i < N; ++i) {
         shortestDist[i] = LIMIT;
      }

      shortestDist[pos] = 0;
      queue <ll> bfs;
      vector <bool> vis(N);
      bfs.push(pos);


      while (!bfs.empty()) {
         ll u = bfs.front();
         bfs.pop();

         if (vis[u]) continue;
         vis[pos] = true;

         for (ll v : g[u]) {
            if (!vis[v] and shortestDist[v] > shortestDist[u] + 1) {
               shortestDist[v] = shortestDist[u] + 1;
               bfs.push(v);
            }
         }
      }

      // cost (i, j) -> get ith coin to pos using atmost j edges as additional help
      for (ll i = 0; i < S; ++i) {
         for (ll j = 0; j < N; ++j) {
            cost[i][j] = LIMIT;
         }
      }

      // base case for dp
      for (ll coin = 0; coin < S; ++coin) {
         cost[coin][0] = LIMIT;
         for (const auto &recipe: rec[coin]) {
            ll recValue = 0;
            for (ll helperCoin : recipe) { // atmost 3 elements
               ll curMinCoin = LIMIT;
               for (ll s : availPos[helperCoin]) {
                  curMinCoin = min(curMinCoin, shortestDist[s]);
               }
               recValue += curMinCoin;
            }
            cost[coin][0] = min(cost[coin][0], recValue);
         }
      }

      // dp for cost
      for (ll j = 1; j < N; ++j) {
         for (ll coin = 0; coin < S; ++coin) {
            ll mnValue = cost[coin][j - 1];
            for (const auto &recipe : rec[coin]) {
               ll recValue = 0;
               for (ll helperCoin : recipe) {
                  recValue += cost[helperCoin][j - 1];
               }
               mnValue = min(recValue, mnValue);
            }
            cost[coin][j] = mnValue;
         }
      }
      res = min(res, cost[0][N - 1]);
   }

   if (res >= LIMIT) {
      cout << -1 << '\n';
   }
   else {
      cout << res << '\n';
   }
}

signed main()
{
  IOS; PREC;
  preproc();

  ll tc = 1;
  cin >> tc;
  for (ll Tt = 1; Tt <= tc; ++Tt) {
    cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
