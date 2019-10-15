#include <iostream>
#include <cstring>
using namespace std;
int R, C;
const int SZ = 101;
int mat[SZ][SZ];
bool visited[SZ][SZ];
bool minHt[10002];
#define LL long long
int dx[] = { -1, 0, 0, 1 };
int dy[] = { 0, 1, -1, 0 };
inline bool IsBorder(int x, int y)
{
   if (x == 1 || y == 1 || x == R || y == C)
      return true;
   return false;
}
/// dfs to get minimum Neghbour height og given cell or group of cells of equal height
int get_min(int i, int j, int minNbr)
{
   visited[i][j] = true;
   for (int d = 0; d < 4; d++)
   {
      int _x = i + dx[d];
      int _y = j + dy[d];
      if (mat[i][j] == mat[_x][_y])
      {
         if (visited[_x][_y] == false)
         {
            if (IsBorder(_x, _y) == false)
               minNbr = get_min(_x, _y, minNbr);
            else
            {    /// this was missing I was ignoring comparing neighbour if its BORDER.
               // DFS is not required (as water will start flowing out) on BORDER but height needs to be compared
               if (minNbr > mat[_x][_y])
                  minNbr = mat[_x][_y];
            }
         }
      }
      else  // greater
      {
         if (minNbr > mat[_x][_y])
            minNbr = mat[_x][_y];
      }
   }
   return minNbr;
}
/// dfs to fill the cell or grp of cells with the given amount of water.  can be optimized save pts in que during get min and fill
LL  _fill(int i, int j, int noTofill)
{
   visited[i][j] = false; // reverse
   LL water = 0;
   for (int d = 0; d < 4; d++)
   {
      int _x = i + dx[d];
      int _y = j + dy[d];
      if (mat[_x][_y] == mat[i][j] && IsBorder(_x, _y) == false && visited[i][j] == true)
      {
         water = water + _fill(_x, _y, noTofill);
      }

   }
   water = water + (noTofill - mat[i][j]);
   mat[i][j] = noTofill;
   return water;

}
LL scan(int ht)
{
   LL fill_count = 0;
   for (int i = 2; i <= R - 1; i++)
   {
      for (int j = 2; j <= C - 1; j++)
      {
         if (mat[i][j] == ht)
         {
            memset(visited, false, sizeof(visited));
            int  MIN = get_min(i, j, 1 << 30);
            if (MIN > ht)
               fill_count = fill_count + _fill(i, j, MIN);
            else
               cout << "";
         }

      }
   }
   return fill_count;
}

int main()
{
   std::ios_base::sync_with_stdio(false);
#ifdef _WIN32
   freopen("SPOJ_WATER.txt", "r", stdin);
#endif
   int T;
   cin >> T;
   while (T--)
   {
      cin >> R >> C;
      memset(minHt, false, sizeof(minHt));
      for (int i = 1; i <= R; i++)
      {
         for (int j = 1; j <= C; j++)
         {
            cin >> mat[i][j];
            if (IsBorder(i, j) == false)
               minHt[mat[i][j]] = true;
         }
      }
      LL TOTAL = 0;
      LL filled = 0;
      for (int i = 1; i <= 10000; i++)
      {
         if (minHt[i] == true)
         {
            filled = scan(i);
            TOTAL = TOTAL + filled;
         }

      }

      cout << TOTAL << endl;;
   }
   return 0;
}

