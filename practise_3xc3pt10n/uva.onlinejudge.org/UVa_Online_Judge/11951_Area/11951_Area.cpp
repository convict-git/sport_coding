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

const int N = 105;
ll P[N][N];
int n, m;
ll k;

void solve(int tc) {
   for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
   {
      if (i > 0) P[i][j] += P[i-1][j];
      if (j > 0) P[i][j] += P[i][j-1];
      if (i > 0 && j > 0) P[i][j] -= P[i-1][j-1];
   }

   ll mx_area = 0, min_cost = 0;
   for (int ax = 0; ax < n; ++ax) for (int bx = ax; bx < n; ++bx)
      for (int ay = 0; ay < m; ++ay) for (int by = ay; by < m; ++by)
      {
         ll cost = P[bx][by];
         if (ax > 0) cost -= P[ax-1][by];
         if (ay > 0) cost -= P[bx][ay-1];
         if (ax > 0 && ay > 0) cost += P[ax-1][ay-1];

         if (cost <= k) {
            if (mx_area < (bx-ax+1)*(by-ay+1)) {
               mx_area = (bx-ax+1)*(by-ay+1);
               min_cost = cost;
            }
            else if (mx_area == (bx-ax+1)*(by-ay+1)) {
               min_cost = min(cost, min_cost);
            }
            else continue;
         }
      }

   cout << "Case #" << tc << ": " << mx_area << ' ' << min_cost << '\n';
}

void read() {
   cin >> n >> m >> k;
   for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
      cin >> P[i][j];
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   for (int i = 1; i <= tc; ++i) {
      read();
      solve(i);
   }

   return EXIT_SUCCESS;
}

