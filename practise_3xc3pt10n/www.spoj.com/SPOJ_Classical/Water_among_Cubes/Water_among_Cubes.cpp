#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ]"
#define x        first
#define y        second

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

const int N = 110;
using pii = pair <int, int>;

int n, m;
int max_water_stored, max_level, min_level;
int Mat[N][N];
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

set <int> levels_set;

inline bool is_valid (int r, int c, int level) {
   return r >= 0 && c >= 0 && r < n && c < m && Mat[r][c] >= level;
}

vector < vector <pii> > level_adj;
void bfs (int r, int c, int level) {
   // debug(r, c, level);
   queue <pii> q;
   vector <bool> vis;
   vis.assign(n * m, false);

   vector <pii> update;
   bool ok = true;
   q.push(pii(r, c));
   vis[m * r + c] = true;

   while (!q.empty()) {
      pii tmp = q.front();
      q.pop();
      update.push_back(tmp);

      for (int dir = 0; dir < 4; ++dir) {
         int rr = tmp.x + dx[dir], cc = tmp.y + dy[dir];
         if (is_valid (rr, cc, level)) {
            if (!vis[m * rr + cc] && Mat[rr][cc] == level) {
               q.push(pii(rr, cc));
               vis[m * rr + cc] = true;
            }
         }
         else {
            ok = false;
            break;
         }
      }
   }

   if (ok) {
      // cerr << "OK true\n";
      for (pii it : update) {
         // debug(it.x, it.y);
         Mat[it.x][it.y] += 1;
         level_adj[Mat[it.x][it.y]].push_back(pii(it.x, it.y));
         max_water_stored += 1;
      }
   }
}

void solve() {
   for (int level = min_level; level <= max_level; ++level) {
      // debug(level, min_level, max_level);
      for (pii it : level_adj[level])
            if (Mat[it.x][it.y] == level)
               bfs(it.x, it.y, level);
   }
   cout << max_water_stored << '\n';
}

void init() {
   level_adj.assign(10010, vector <pii> ());
   levels_set.clear();
   max_water_stored = 0;
   min_level = INT_MAX, max_level = INT_MIN;
}

void read() {
   init();
   cin >> n >> m;
   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
         cin >> Mat[i][j];
         max_level = max(max_level, Mat[i][j]);
         min_level = min(min_level, Mat[i][j]);
         level_adj[Mat[i][j]].push_back(pii(i, j));
      }
   }
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

