#include      <bits/stdc++.h>
#include      <ext/pb_ds/assoc_container.hpp>
#include      <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#pragma GCC   optimize ("Ofast")
#pragma GCC   optimize ("unroll-loops")
#pragma GCC   target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS   ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC  cout.precision (10); cout << fixed
#define x     first
#define y     second
#define bg(x) " [ " << #x << " : " << (x) << " ] "
#define un(x) sort(x.begin(), x.end()), \
              x.erase(unique(x.begin(), x.end()), x.end())
using   ll  = long long;
using   ull = unsigned long long;
using   ff  = long double;
using   pii = pair<int,int>;
using   pil = pair<int,ll>;
typedef tree
< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
ordered_set;

struct chash {
   int operator()(pii x) const { return x.x*31 + x.y; }
};
gp_hash_table <pii, int, chash> mp;

seed_seq seq{
   (uint64_t) chrono::duration_cast<chrono::nanoseconds>
      (chrono::high_resolution_clock::now().time_since_epoch()).count(),
      (uint64_t) __builtin_ia32_rdtsc(),
      (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]

#define debug(args...) { \
   /* WARNING : do NOT compile this debug func calls with following flags: // \
    * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); \
   istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) {
   it->empty(); cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
   cerr << fixed << setprecision(15)
      << " [ " <<  *it << " : " << a  << " ] "<< ' ';
   err(++it, args...);
}
/*****************************************************************************/

const int N = 500;
const int infi = (int)1e9;
vector <string> mat;
int n, m;
int dist[N][N][3];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};
int sx, sy, ex, ey;

inline bool is_valid(int x, int y) {
   return x >= 0 && y >= 0 && x < n && y < m && mat[x][y] == '.';
}

inline bool no_hurdle(int x, int y, int len, int dir) {
   for (int i = 1; i <= len; ++i) {
      int X = x + i * dx[dir], Y = y + i * dy[dir];
      if (!is_valid(X, Y)) return false;
   }
   return true;
}

int bfs() {
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
         for (int k = 0; k < 3; ++k)
            dist[i][j][k] = infi;

   dist[sx][sy][0] = 0;
   queue <pair <pii, int>> q;
   q.push({{sx, sy}, 0});

   while (!q.empty()) {
      pair <pii, int> foo = q.front();
      q.pop();

      int xx = foo.x.x, yy = foo.x.y;
      int state = foo.y;
      if (xx == ex && yy == ey) {
         return dist[ex][ey][state];
      }
      for (int dir = 0; dir < 4; ++dir) {
         int X = xx + (state + 1) * dx[dir], Y = yy + (state + 1) * dy[dir];
         if (no_hurdle(xx, yy, state + 1, dir) && dist[X][Y][(state + 1) % 3] == infi) {
            dist[X][Y][(state + 1) % 3] = dist[xx][yy][state] + 1;
            q.push({{X, Y}, (state + 1) % 3});
         }
      }
   }
   return infi;
}

void solve() {
   int ans = bfs();
   if (ans == infi) cout << "NO\n";
   else cout << ans << '\n';
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      cin >> n >> m;
      mat.clear();
      for (int i = 0; i < n; ++i) {
         string foo;
         cin >> foo;

         mat.push_back(foo);
         for (int j = 0; j < m; ++j)  {
            if (mat[i][j] == 'S') sx = i, sy = j, mat[i][j] = '.';
            if (mat[i][j] == 'E') ex = i, ey = j, mat[i][j] = '.';
         }
      }
      solve();
   }

   return EXIT_SUCCESS;
}
