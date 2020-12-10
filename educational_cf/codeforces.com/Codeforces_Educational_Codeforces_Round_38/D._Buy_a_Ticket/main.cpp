#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

const int mxn = 2e5 + 10;
vector <pair <int, long long>> g[mxn];
int n, m;
long long ar[mxn];
int vis[mxn];

class cmp {
   public:
      bool operator () (const int &p, const int &q) {
         return ar[p] > ar[q];
      }
};
void preproc() {
}

void solve() {
   cin >> n >> m;
   for (int e = 0, u, v; e < m; ++e) {
      long long w;
      cin >> u >> v >> w;
      --u, --v;
      g[u].push_back({v, w});
      g[v].push_back({u, w});
   }
   set <pair <long long, int>> s;
   for (int i = 0; i < n; ++i) {
      cin >> ar[i];
      vis[i] = 0;
      s.insert({ar[i], i});
   }

   while (!s.empty()) {
      auto el=*s.begin();
      int u=el.second;
      long long aval=el.first;
      s.erase(s.begin());
      if (vis[u]) continue;
      vis[u]=1;
      ar[u] = aval;
      for (auto ele : g[u]) {
         int v=ele.first;
         long long w=ele.second;
         if (!vis[v] and ar[v] > ar[u] + w*2) {
            ar[v] = ar[u] + w*2;
            s.insert({ar[v], v});
         }
      }
   }
   for (int i = 0; i < n; ++i) {
      cout << ar[i] << " \n"[i == n-1];
   }
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  // cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
