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

const int N = 200;
int mat[N][N];
int n, m, idx, line_cnt;
string B, D, st;

void B_to_D(int r, int c, int rr, int cc) {
   if (rr < r || cc < c) return;
   bool is_one = 1, is_zero = 0;
   for (int i = r; i <= rr; ++i) {
      for (int j = c; j <= cc; ++j){
         is_one &= mat[i][j];
         is_zero |= mat[i][j];
      }
   }
   is_zero ^= 1;
   if (line_cnt == 50) {
      line_cnt = 0;
      cout << '\n';
   }
   if (!is_one && !is_zero) {
      cout << "D";
      ++line_cnt;
      int mr = (r + rr)/2, mc = (c + cc)/2;
      B_to_D(r, c, mr, mc);
      B_to_D(r, mc + 1, mr, cc);
      B_to_D(mr + 1, c, rr, mc);
      B_to_D(mr + 1, mc + 1, rr, cc);
   }
   else {
      if (is_one) cout << "1";
      else cout << "0";
      ++line_cnt;
   }
   return;
}

void D_to_B(int r, int c, int rr, int cc) {
   if (rr < r || cc < c) return;
   char val = B[idx];
   ++idx;
   if (val == 'D') {
      int mr = (r + rr)/2, mc = (c + cc)/2;
      D_to_B(r, c, mr, mc);
      D_to_B(r, mc + 1, mr, cc);
      D_to_B(mr + 1, c, rr, mc);
      D_to_B(mr + 1, mc + 1, rr, cc);
   }
   else {
      for (int i = r; i <= rr; ++i)
         for (int j = c; j <= cc; ++j)
            mat[i][j] = val - '0';
   }
   return;
}

void read() {
   if (st == "B") {
      int cnt = n*m;
      D = "";
      while (cnt) {
         cin >> st;
         D += st;
         cnt -= (int) st.size();
      }
      cout << "D" << setw(4) << n << setw(4) << m << '\n';

      for (int i = 0; i < n; ++i) {
         for (int j = 0; j < m; ++j) {
            mat[i][j] = D[m*i + j] - '0';
         }
      }
      line_cnt = 0;
      B_to_D(0, 0, n - 1, m - 1);
      cout << '\n';
   }
   else {
      cin >> B;
      cout << "B" << setw(4) << n << setw(4) << m << '\n';
      idx = 0;
      D_to_B(0, 0, n - 1, m - 1);
      line_cnt = 0;
      for (int i = 0; i < n; ++i) {
         for (int j = 0; j < m; ++j) {
            cout << mat[i][j];
            ++line_cnt;
            if (!(j == m - 1 && i == n - 1) && line_cnt == 50) {
               line_cnt = 0;
               cout << "\n";
            }
         }
      }
      cout << '\n';
   }
}

signed main() {
   IOS; PREC;
   while (cin >> st >> n >> m, st != "#") {
      read();
   }
   return EXIT_SUCCESS;
}

