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
const int N = 21;
ll mat[N][N][N];
ll cum[N][N][N];
int n, m, h; // row col height

ll sum_rect(int ax, int ay, int bx, int by, int k) {
   ll ans = cum[bx][by][k];
   if (ax > 0) ans -= cum[ax-1][by][k];
   if (ay > 0) ans -= cum[bx][ay-1][k];
   if (ax > 0 && ay > 0) ans += cum[ax-1][ay-1][k];
   return ans;
}

void rect_cum() {
   // find height wise cumulative
   for (int k = 0; k < h; ++k)
      for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
      {
         ll tmp = 1ll*mat[i][j][k];
         if (i > 0) tmp += cum[i-1][j][k];
         if (j > 0) tmp += cum[i][j-1][k];
         if (i > 0 && j > 0) tmp -= cum[i-1][j-1][k];
         cum[i][j][k] = tmp;
      }
}

void solve() {
   rect_cum();
   //apply kadane's method
   ll mx_sum = LLONG_MIN;
   for (int il = 0; il < n; ++il) for (int ih = il; ih < n; ++ih)  // o(N^4 * N)
      for (int jl = 0; jl < m; ++jl) for (int jh = jl; jh < m; ++jh)
      {
         ll cur_sum = 0;
         for (int k = 0; k < h; ++k) {
            cur_sum += sum_rect(il, jl, ih, jh, k);
            mx_sum = max(cur_sum, mx_sum);
            if (cur_sum < 0) cur_sum = 0;
         }
      }

   cout << mx_sum << '\n';
}

void read() {
   cin >> n >> m >> h;
   for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
      for (int k = 0; k < h; ++k) cin >> mat[i][j][k];
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   for (int i = 0; i < tc; ++i) {
      if (i) cout << '\n';
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

