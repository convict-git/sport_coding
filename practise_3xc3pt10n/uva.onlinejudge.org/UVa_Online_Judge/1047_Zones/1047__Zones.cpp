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

const int N = 20, M = 10;
struct el {
   int bit, val, len;
} el[M];

int sz[N];
int n, actual, m;

void read() {
   for (int i = 0; i < n; ++i)
      cin >> sz[i];

   cin >> m;
   for (int i = 0; i < m; ++i) {
      el[i] = {0, 0, 0};
      int len; cin >> len;
      el[i].len = len;
      while (len--) {
         int idx; cin >> idx;
         --idx;
         el[i].bit |= (1 << idx);
      }
      cin >> el[i].val;
   }
}

void solve(int tc) {
   int mx_val = INT_MIN, best_sset = 0;

   for (int sub_set = 0; sub_set < (1 << n); ++sub_set) {
      int val = 0;
      if (__builtin_popcount(sub_set) == actual) {
         for (int j = 0; j < n; ++j)
            if (sub_set & (1 << j)) val += sz[j];

         for (int j = 0; j < m; ++j) {
            if ((sub_set & el[j].bit)) {
               int cnt = __builtin_popcount(sub_set & el[j].bit);
               val -= el[j].val * (cnt - 1);
            }
         }
         if (mx_val <= val) {
            if (mx_val < val || (sub_set & (-sub_set)) < (best_sset & (-best_sset)))
               best_sset = sub_set;
            mx_val = val;
         }
      }
   }

   cout << "Case Number  " << tc << '\n';
   cout << "Number of Customers: " << mx_val << '\n';
   cout << "Locations recommended: ";
   for (int i = 0, f = 0; i < n; ++i) {
      if (best_sset & (1 << i)) {
         if (!f) ++f;
         else cout << ' ';
         cout << i + 1;
      }
   }
   cout << "\n\n";
}

signed main() {
   IOS; PREC;

   int tc = 1;
   while (cin >> n >> actual, n || actual) {
      read();
      solve(tc++);
   }
   return EXIT_SUCCESS;
}

