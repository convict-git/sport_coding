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

const int Maxn = 52;
int N;
int vis[Maxn];
int canGo[Maxn][2];

void preproc()
{
}

void dfs (int src) {
   vis[src] = true;
   if (src - 1 >= 0 and !vis[src - 1] and canGo[src][0] == 0) {
      dfs(src - 1);
   }
   if (src + 1 < N and !vis[src + 1] and canGo[src][1] == 0) {
      dfs(src + 1);
   }
}

void solve()
{
   string in, out;
   cin >> N >> in >> out;

   memset(canGo, 0, sizeof(canGo));
   for (int i = 0; i < N; ++i) {
      if (in[i] == 'N') {
         if (i - 1 >= 0) canGo[i - 1][1] = -1;
         if (i + 1 < N) canGo[i + 1][0] = -1;
      }
      if (out[i] == 'N') {
         canGo[i][0] = -1;
         canGo[i][1] = -1;
      }
   }
   for (int i = 0; i < N; ++i) {
      memset(vis, 0, sizeof(vis));
      dfs(i);
      for (int j = 0; j < N; ++j) {
         cout << (vis[j] ? 'Y' : 'N');
      }
      cout << '\n';
   }
}

signed main()
{
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    cout << "Case #" << Tt << ":\n";
    solve();
  }
  return EXIT_SUCCESS;
}
