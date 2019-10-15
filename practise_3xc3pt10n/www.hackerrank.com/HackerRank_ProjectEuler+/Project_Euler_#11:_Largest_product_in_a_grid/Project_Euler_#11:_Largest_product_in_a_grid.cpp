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
const int N = 20;
int mat[N][N];

signed main() {
   IOS; PREC;
   int n = N, mx_val = 0;

   for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
         cin >> mat[i][j];
         if (i >= 3) mx_val = max(mx_val, mat[i][j]*mat[i-1][j]*mat[i-2][j]*mat[i-3][j]);
         if (j >= 3) mx_val = max(mx_val, mat[i][j]*mat[i][j-1]*mat[i][j-2]*mat[i][j-3]);
         if (i >= 3 && j >= 3) mx_val = max(mx_val, mat[i][j]*mat[i-1][j-1]*mat[i-2][j-2]*mat[i-3][j-3]);
         if (n - i >= 4 && i >= 3) mx_val = max(mx_val, mat[i][j]*mat[i-1][j+1]*mat[i-2][j+2]*mat[i-3][j+3]);
      }
   }
   cout << mx_val << '\n';


   return EXIT_SUCCESS;
}

