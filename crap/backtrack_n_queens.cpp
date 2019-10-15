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

const int N = 15;
int board[N][N] = {0};
int n;
int sol = 0;
bitset <30> row, l_diag, r_diag;

void backtrack(int c) {
   if (c == n) {
      ++sol;
      return;
   }

   for (int r = 0; r < n; ++r) {
      if (board[r][c] != 1 && !row[r] && !l_diag[r - c + n - 1]  && !r_diag[r + c]) {
         row[r] = l_diag[r - c + n - 1] = r_diag[r + c] = true;
         backtrack(c + 1);
         row[r] = l_diag[r - c + n - 1] = r_diag[r + c] = false;
      }
   }
}

signed main() {
   IOS; PREC;

   for (n = 0; n < 13; ++n) {
      sol = 0;
      row.reset();
      l_diag.reset();
      r_diag.reset();
      backtrack(0);
      cout <<  n << " " << sol << '\n';
   }

   return EXIT_SUCCESS;
}
