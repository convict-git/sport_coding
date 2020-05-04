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
const int N = 504;
int mat[N][N];
int n, m, L, U, mx_sz;

void solve() {
   int q; cin >> q;
   while(q--) {
      cin >> L >> U;
      assert(L <= U);
      mx_sz = INT_MIN;

      for (int row = 0; row < n; ++row) {
         int l = 0, h = m - 1, g, col, sz;
         while (l <= h) {
            g = (l + h)/2;
            if (mat[row][g] >= L) h = g - 1;
            else l = g + 1;
         }
         if (l == m) continue;
         col = l;

         l = 0, h = min(n - row, m - col) - 1; //size = ans + 1
         while (l <= h) {
            g = (l + h)/2;
            if (mat[row + g][col + g] <= U) l = g + 1;
            else h = g - 1;
         }
         sz = h + 1;
         mx_sz = max(mx_sz, sz);
         // debug(l, g, h, row, col, mat[row][col], mat[row+h][col+h]);
      }
      if (mx_sz == INT_MIN) mx_sz = 0;
      cout << mx_sz << "\n";
   }
   cout << "-\n";
}

void read() {
   for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
         cin >> mat[i][j];
}

signed main() {
   IOS; PREC;
   while (cin >> n >> m, n || m) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

