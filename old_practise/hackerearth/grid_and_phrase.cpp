#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#include         <iostream>
#include         <iomanip>
#include         <functional>
#include         <algorithm>
#include         <unordered_map>
#include         <vector>
#include         <map>
#include         <set>
#include         <chrono>
#include         <queue>
#include         <random>
#include         <string>
#include         <cstring>
#include         <climits>
#include         <cstdlib>
#include         <cmath>
#include         <iomanip>
#include         <cassert>
#define x        first
#define y        second
using namespace std;

const int N = 110;
char Mat[N][N];
int n, m;
int dx[] = {1, 0, 1, -1};
int dy[] = {1, 1, 0, 1};
string saba = "saba";
int ans;

void read() {
   cin >> n >> m;
   string s;
   for (int r = 0; r < n; ++r) {
      cin >> s;
      assert(int(s.size()) == m);
      for (int c = 0; c < m; ++c) {
         Mat[r][c] = s[c];
      }
   }
}

bool isValid (int xx, int yy) {
   return xx >= 0 && yy >= 0 && xx < n && yy < m;
}

void deep (int xx, int yy, int dep, int dir) {
   xx += dx[dir], yy += dy[dir];
   if (!isValid(xx, yy)) return;
   if (Mat[xx][yy] == saba[dep]) {
      if (dep == 3) ++ans;
      else deep (xx, yy, dep + 1, dir);
   }
}

void solve() {
   ans = 0;
   for (int r = 0; r < n; ++r) {
      for (int c = 0; c < m; ++c) {
         if (Mat[r][c] == 's') {
            for (int dir = 0; dir < 4; ++dir) {
               deep (r, c, 1, dir);
            }
         }
      }
   }
   cout << ans << '\n';
}

signed main() {
   IOS; PREC;
   read();
   solve();
	return EXIT_SUCCESS;
}

