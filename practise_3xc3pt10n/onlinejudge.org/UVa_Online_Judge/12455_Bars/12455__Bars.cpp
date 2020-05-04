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
int len[N];
int req_len, n;

bool solve() {
   for (int sub_set = 0; sub_set < (1 << n); ++sub_set) {
      int val = 0;
      for (int j = 0; j < n; ++j) {
         if (sub_set & (1 << j)) val += len[j];
      }
      if (val == req_len) return true;
   }
   return false;
}

void read() {
   cin >> req_len;
   cin >> n;
   for (int i = 0; i < n; ++i) cin >> len[i];
}

signed main() {
   IOS; PREC;
   int tc; cin >> tc;
   while (tc--) {
      read();
      cout << (solve() ? "YES\n" : "NO\n");
   }

   return EXIT_SUCCESS;
}

