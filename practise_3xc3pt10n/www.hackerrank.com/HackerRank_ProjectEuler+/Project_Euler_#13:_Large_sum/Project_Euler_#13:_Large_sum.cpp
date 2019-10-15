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

const int N = 1005;
int n;
int mat[N][50];

signed main() {
   IOS; PREC;
   cin >> n;
   string st;
   for (int i = 0; i < n; ++i) {
      cin >> st;
      reverse(st.begin(), st.end());
      for (int j = 0; j < 50; ++j) {
         mat[i][j] = st[j] - '0';
      }
   }

   vector <int> sum;
   int car = 0;
   for (int i = 0; i < 50; ++i) {
      int cur = 0;
      for (int j = 0; j < n; ++j) {
         cur += mat[j][i];
      }
      cur += car;
      sum.push_back(cur % 10);
      car = cur/10;
   }
   while (car) sum.push_back(car%10), car /= 10;
   reverse(sum.begin(), sum.end());

   for (int i = 0; i < 10; ++i)
      cout << sum[i];
   cout << '\n';

   return EXIT_SUCCESS;
}

