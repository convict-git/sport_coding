#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ] "
#define x        first
#define y        second
using ll = long long;
using ld = long double;
using pii = pair<int,int>;

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
const int N = int(1e4) + 10;
vector <int> ht, wd;
int Inc[N], Dec[N];
int n; //n <= 1000

void solve(int tc) {
   for (int i = 0; i < n; ++i) {
      Dec[i] = Inc[i] = wd[i];
      int mx_inc = 0, mx_dec = 0;
      for (int j = 0; j < i; ++j) {
         if (ht[j] > ht[i]) {
            mx_dec = max(Dec[j], mx_dec);
         }
         else if (ht[j] < ht[i]) {
            mx_inc = max(Inc[j], mx_inc);
         }
      }
      Dec[i] += mx_dec;
      Inc[i] += mx_inc;
   }
   int LIS = 0, LDS = 0;
   for (int i = 0; i < n; ++i) LIS = max(LIS, Inc[i]);
   for (int i = 0; i < n; ++i) LDS = max(LDS, Dec[i]);
   cout << "Case " << tc << ". ";
   if (LIS >= LDS) {
      cout << "Increasing (" << LIS << "). Decreasing (" << LDS << ").\n";
   }
   else {
      cout << "Decreasing (" << LDS << "). Increasing (" << LIS << ").\n";
   }
}

void read() {
   cin >> n;
   ht.assign(n, 0);
   wd.assign(n, 0);
   assert(n < N);
   for (int i = 0; i < n; ++i) cin >> ht[i];
   for (int i = 0; i < n; ++i) cin >> wd[i];
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   for (int i = 1; i <= tc; ++i) read(), solve(i);

   return EXIT_SUCCESS;
}
