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

const int N = (int)1e4 + 10;
int books[N];
int n, m;

struct ans {
   int x, y;
   ans (int _x, int _y) : x(min(_x, _y)), y(max(_x, _y)) {};
   inline bool operator < (const ans &o) const {
      return abs(x - y) < abs(o.x - o.y);
   }
};

void solve() {
   sort (books, books + n);
   ans Ans = {0, INT_MAX};
   for (int i = 0; i < n; ++i) {

      int val = m - books[i], l = i + 1, h = n - 1;
      if (val <= 0) continue;

      while (l <= h) {
         int g = (l + h)/2;
         if (books[g] < val) l = g + 1;
         else h = g - 1;
      }
      if (l != n && books[l] == val) {
         assert(books[i] + books[l] == m);
         Ans = min(Ans, ans({books[i], books[l]}));
      }
   }
   cout << "Peter should buy books whose prices are " << Ans.x << " and " << Ans.y << ".\n\n";
}

signed main() {
   IOS; PREC;
   while (cin >> n) {
      for (int i = 0; i < n; ++i) {
         cin >> books[i];
      }
      cin >> m;
      solve();
   }

   return EXIT_SUCCESS;
}

