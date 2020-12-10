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

const int Maxn = 1e6 + 10;
int N, M;
int vis[Maxn];
int firstElement, lastElement;
typedef long long ll;
ll sumAll = 0;

void preproc()
{
}

void solve()
{
   memset(vis, 0, sizeof(vis));
   cin >> N >> M;
   sumAll = (1ll*N*(N + 1)) / 2;
   for (int i = 1; i <= N; ++i) {
      vis[i] = true;
   }
   firstElement = 1, lastElement = N;

   while (M--) {
      int op;
      cin >> op;
      if (vis[op]) {
         swap(firstElement, lastElement);
      }
      else {
         vis[op] = true;
         vis[lastElement] = false;
         sumAll += op - lastElement;
         lastElement = op;
      }
      cout << sumAll << '\n';
   }
}

signed main()
{
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
