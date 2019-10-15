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


const int N = 8;
int mat[N][N];
bitset <8> row_mask, col_mask;
int rows, cols, n;

int solve(int bit, int rr, int level) {
   // debug(level);
   if (!bit) { // select row
      int mx_val = INT_MIN;
      for (int r = 0; r < rows; ++r) {
         if (!row_mask[r]) {
            row_mask[r] = true;
            mx_val = max(mx_val, solve(bit ^ 1, r, level));
            row_mask[r] = false;
         }
      }
      return mx_val;
   }
   else {
      int mn_val = INT_MAX;
      for (int c = 0; c < cols; ++c) {
         if (!col_mask[c]) {
            col_mask[c] = true;
            if (level == n - 1) mn_val = min(mn_val, mat[rr][c]);
            else mn_val = min(mn_val, mat[rr][c] + solve(bit ^ 1, rr, level + 1));
            col_mask[c] = false;
         }
      }
      return mn_val;
   }
}

void read() {
   cin >> n;
   rows = cols = n;
   row_mask.reset(), col_mask.reset();

   for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
         cin >> mat[r][c];
      }
   }
   cout << solve(0, -1, 0) << '\n';
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      read();
   }

   return EXIT_SUCCESS;
}

