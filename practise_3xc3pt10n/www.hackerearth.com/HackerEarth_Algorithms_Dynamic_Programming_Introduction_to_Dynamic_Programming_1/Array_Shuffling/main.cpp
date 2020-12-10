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

int N;
const int Maxn = 110;
int cache[Maxn][Maxn][Maxn];
vector <vector <int>> Ar;

void preproc()
{
}

/* rec : (pos, fi, se) -> max of sum of length of two non-decreasing non-intersecting subsequence
 *                        considering the elements with index [0..pos], first seq ends at fi,
 *                        while second seq ends at se
 */
int rec (int pos, int fi, int se)
{
   if (pos == N) { // gone out of bounds
      return 0;
   }
   if (cache[pos][fi][se] != -1) { // if already cached
      return cache[pos][fi][se];
   }
   int &res = cache[pos][fi][se]; // reference to the new update position

   for (int ch = 0; ch <= 2; ++ch) { // 0 -> none, 1 -> one from this pos, 2 -> two from this pos
      if (ch == 0) { // none taken from this position
         res = max(res, rec(pos + 1, fi, se));
      }
      else {
         vector <int> perm = {0, 1, 2}; // to permuate among all possible shuffles for a fixed position pos
         do {
            if (ch == 1) { // one taken from this position
               int cur = Ar[perm[0]][pos];

               if (cur >= fi) { // if current element is greater eq to end of first seq, then take it
                  res = max(res, 1 + rec(pos + 1, cur, se));
               }
               if (cur >= se) { // if current element is greater eq to end of second seq, then take it
                  res = max(res, 1 + rec(pos + 1, fi, cur));
               }
            }
            else { // two taken from this pos
               int curx = Ar[perm[0]][pos], cury = Ar[perm[1]][pos];

               if (curx >= fi and cury >= se) { // keep curx as new first end, cury as new second end
                  res = max(res, 2 + rec(pos + 1, curx, cury));
               }
               if (cury >= fi and curx >= se) { // keep cury as new first end, curx as new second end
                  res = max(res, 2 + rec(pos + 1, cury, curx));
               }
            }
         } while (next_permutation(perm.begin(), perm.end()));
      }
   }
   return res;
}

void solve()
{
   cin >> N;
   Ar.assign(3, vector <int> (N));

   for (int rot = 0; rot < 3; ++rot) {
      for (int i = 0; i < N; ++i) {
         cin >> Ar[rot][i];
      }
   }
   memset(cache, -1, sizeof(cache));

   cout << rec(0, 0, 0) << '\n'; // start with 0 values for both first and second seq ends
   return;
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
