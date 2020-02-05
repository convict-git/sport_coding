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
using ll = long long;

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
const int N = 2005;
vector <string> mat;
vector <vector <pair <int, int>>> pos;
int n, m, mx_char;
int mask = 0;
struct solution {
  int xa, ya, xb, yb;
};
solution hash_sol;
bool hash_ok;
vector <solution> sol;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
inline bool is_valid(int xx, int yy) {
  return xx >= 0 && yy >= 0 && xx < n && yy < m;
}

void init() {
  mask = 0;
  mx_char = -1;
  hash_sol = {-1, -1, -1, -1};
  hash_ok = false;
  pos.assign(26, vector <pair <int,int>>());
  sol.clear();
  mat.clear();
}

void read() {
  cin >> n >> m;
  string st;
  for (int i = 0; i < n; ++i) {
    cin >> st;
    mat.push_back(st);
    assert((int)st.size() == m);

    for (int j = 0; j < m; ++j) {
      if (mat[i][j] == '.') continue;
      char ch = mat[i][j];
      mx_char = max(mx_char, int(ch - 'a'));
      pos[int(ch-'a')].push_back(pair <int,int>(i,j));
      mask |= (1 << int(ch - 'a'));
    }
  }
}

void solve() {
  bool ok = true;

  for (int i = mx_char; i >= 0 && ok; --i) {
    if (mask & (1 << i)) { // present
      //find direction
      int xx = pos[i][0].x, yy = pos[i][0].y;
      int sol_len = 1;
      int this_dir = -1;

      for (int dir = 0; dir < 4; ++dir) {
        int X = xx + dx[dir], Y = yy + dy[dir];
        while (is_valid(X, Y) && (mat[X][Y] == '#' || mat[X][Y] == char(i + 'a'))) {
          if (mat[X][Y] == char(i + 'a')) this_dir = dir;
          X = X + dx[dir], Y = Y + dy[dir];
        }
        if (this_dir != -1) break;
      }
      //change all to '#'

      mat[xx][yy] = '#';
      if (this_dir != -1) {
        int X = xx + dx[this_dir], Y = yy + dy[this_dir];
        while (is_valid(X, Y) && (mat[X][Y] == '#' || mat[X][Y] == char(i + 'a'))) {
          ++sol_len;
          mat[X][Y] = '#';
          X = X + dx[this_dir], Y = Y + dy[this_dir];
        }
      }
      //check if something left
      for (auto le : pos[i]) {
        if (mat[le.x][le.y] != '#') {
          ok = false;
          break;
        }
      }
      //store solution
      if (this_dir == -1) {
        sol.push_back({xx, yy, xx, yy});
        hash_sol = {xx, yy, xx, yy};
      }
      else {
        sol.push_back({xx, yy, xx + dx[this_dir]*(sol_len-1), yy + dy[this_dir]*(sol_len-1)});
        hash_sol = {xx, yy, xx + dx[this_dir]*(sol_len-1), yy + dy[this_dir]*(sol_len-1)};
      }
    }
    else { // not present
      sol.push_back(hash_sol);
    }
  }
  reverse(sol.begin(), sol.end());

  if (ok) {
    cout << "YES\n";
    cout << sol.size() << '\n';
    for (int i = 0; i < (int)sol.size(); ++i) {
      cout << sol[i].xa+1 << ' ' << sol[i].ya+1 << ' ' << sol[i].xb+1 << ' ' << sol[i].yb+1 << '\n';
    }
  }
  else {
    cout << "NO\n";
  }
}

signed main() {
  IOS; PREC;
  int tc;
  cin >> tc;
  for (int i = 1; i <= tc; ++i) {
    init();
    read();
    solve();
  }
  return EXIT_SUCCESS;
}

