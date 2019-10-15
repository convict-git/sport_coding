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

const int N = 75*3 + 10;
int mat[N][N];
int n, m;

void solve() {

   for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
      if (j > 0) mat[i][j] += mat[i][j-1];

   int mx_sum = INT_MIN;
   for (int l = 0; l < m/2; ++l) for (int r = l; r < l + m/2; ++r)
   {
      for (int j = 0; j < n/2; ++j)
         for (int i = j, cur_sum = 0; i < j + n/2; ++i)
      {
         cur_sum += mat[i][r];
         if (l > 0) cur_sum -= mat[i][l-1];
         mx_sum = max(mx_sum, cur_sum);
         if (cur_sum < 0) cur_sum = 0;
      }
   }
   cout << mx_sum << '\n';
}

void read() {
   cin >> n; m = n;
   for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
      cin >> mat[i][j];

   n *= 2, m *= 2;

   for (int i = 0; i < n/2; ++i) for (int j = m/2; j < m; ++j)
      mat[i][j] = mat[i][j-m/2];
   for (int i = n/2; i < n; ++i) for (int j = 0; j < m; ++j)
      mat[i][j] = mat[i-n/2][j];
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   while (tc--) {
      read();
      solve();
   }
   return EXIT_SUCCESS;
}

