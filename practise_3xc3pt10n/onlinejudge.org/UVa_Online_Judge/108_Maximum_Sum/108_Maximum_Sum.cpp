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
int mat[N][N], cum[N][N];
int n, m;

void solve() {
   for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
   {
      cum[i][j] = mat[i][j];
      if (j > 0) cum[i][j] += cum[i][j-1];
   }

   int mx_sum = INT_MIN;
   for (int l = 0; l < m; ++l) for (int h = l; h < m; ++h)
      for (int i = 0, cur_sum = 0; i < n; ++i)
      {
         cur_sum += cum[i][h];
         if (l > 0) cur_sum -= cum[i][l-1];

         mx_sum = max(cur_sum, mx_sum);
         if (cur_sum < 0) cur_sum = 0;
      }
   cout << mx_sum << '\n';
}

void read() {
   cin >> n;
   m = n;
   for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j)
      cin >> mat[i][j];
}

signed main() {
   IOS; PREC;
   read();
   solve();

   return EXIT_SUCCESS;
}

