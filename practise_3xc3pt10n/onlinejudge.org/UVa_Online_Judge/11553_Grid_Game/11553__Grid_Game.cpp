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
int rows, cols, n;

void read() {
   cin >> n;
   rows = cols = n;

   for (int r = 0; r < rows; ++r) {
      for (int c = 0; c < cols; ++c) {
         cin >> mat[r][c];
      }
   }
   vector <int> perm;
   for (int i = 0; i < n; ++i)
      perm.push_back(i);

   int mn = INT_MAX;
   do {
      int val = 0;
      for (int r = 0; r < rows; ++r) {
         val += mat[r][perm[r]];
      }
      mn = min(val, mn);
   } while (next_permutation(perm.begin(), perm.begin() + n));
   cout << mn << '\n';
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

