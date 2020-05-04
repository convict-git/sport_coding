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
const int N = 1003;
int val[N];
int n, m, max_c;

void solve() {
   int l = max_c, h = (int)1e9;

   while (l <= h) {
      int cap = (l + h)/2;

      int cnt = 1;
      for (int i = 0, cur_c = 0; i < n; ++i) {
         if (cur_c + val[i] > cap) {
            ++cnt;
            cur_c = val[i];
         }
         else cur_c += val[i];
      }
      if (cnt > m) l = cap + 1;
      else h = cap - 1;
   }
   cout << l << '\n';
}

void read() {
   max_c = INT_MIN;
   for (int i = 0; i < n; ++i) cin >> val[i], max_c = max(max_c, val[i]);
}

signed main() {
   IOS; PREC;
   while (cin >> n >> m) {
      read();
      solve();
   }

   return EXIT_SUCCESS;
}

