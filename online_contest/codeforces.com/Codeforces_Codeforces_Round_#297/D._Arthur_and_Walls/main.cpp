// Hack it and have it ;) //
/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows!* * * * * * */
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

void preproc()
{
}

void solve()
{
   // take input
   int N, M;
   cin >> N >> M;
   vector <string> mat(N);
   queue <pair <int, int>> bfs;
   for (int i = 0; i < N; ++i) {
      cin >> mat[i];
      assert((int)mat[i].size() == M);
      /*
      for (int j = 0; j < M; ++j) {
         if(mat[i][j] == '*') { // push all the possible pos
            bfs.push({i, j});
         }
      }
      */
   }
   auto is_valid = [&] (int x, int y) -> bool {
      return (x >= 0 and y >= 0 and x < N and y < M);
   };

   auto are_dots = [&]
      (char c1, char c2, char c3) -> bool {
         return c1 == '.' and c2 == '.' and c3 == '.';
   };
   // method to check whether * is alone in any 2x2 matrix
   auto is_alone = [&] (int x, int y) -> bool {
      return
            (is_valid(x-1, y-1) and // top-left
             are_dots(mat[x-1][y-1], mat[x-1][y], mat[x][y-1]))
            or
            (is_valid(x-1, y+1) and // top-right
             are_dots(mat[x-1][y+1], mat[x-1][y], mat[x][y+1]))
            or
            (is_valid(x+1, y+1) and // bottom-right
             are_dots(mat[x+1][y+1], mat[x][y+1], mat[x+1][y]))
            or
            (is_valid(x+1, y-1) and // bottom-left
             are_dots(mat[x+1][y-1], mat[x][y-1], mat[x+1][y]));
   };

   for (int i = 0; i < N; ++i) {
      for (int j = 0; j < M; ++j) {
         if (mat[i][j] == '*' and is_alone(i, j)) {
            bfs.push({i, j});
            debug(i, j);
         }
      }
   }

   int dx[] = {0, -1, 1};
   int dy[] = {1, -1, 0};

   while (!bfs.empty())  {
      auto work = bfs.front();
      bfs.pop();
      if (mat[work.first][work.second] == '.')
         continue;
      if (is_alone(work.first, work.second)) {
         debug(work.first, work.second);
         mat[work.first][work.second] = '.'; // make this a free room
         for (int xx = 0; xx < 3; ++xx) {
            for (int yy = 0; yy < 3; ++yy) {
               int X = work.first + dx[xx];
               int Y = work.second + dy[yy];
               if (is_valid(X, Y) and mat[X][Y] == '*') {
                  bfs.push({X, Y});
               }
            }
         }
      }
   }

   for (int i = 0; i < N; ++i) {
      cout << mat[i] << '\n';
   }
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

