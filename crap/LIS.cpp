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

const int N = (int)1e6 + 10;
int A[N], L[N], Par[N], idx[N];
int n, sz;

void LIS() {
   n = 0;
   sz = 0;
   int tmp;
   while (cin >> tmp) {
      A[n] = tmp, ++n;
   }

   int last_idx = -1;
   for (int i = 0; i < n; ++i) {
      int l = 0, h = sz - 1;
      while (l <= h) {
         int g = (l + h)/2;
         if (A[i] > L[g]) l = g + 1;
         else h = g - 1;
      }
      L[l] = A[i];
      idx[l] = i;
      if (l == sz) ++sz;
      Par[i] = (l == 0 ? -1 : idx[l-1]);
   }

   cout << sz << '\n' << "-\n";
   vector <int> sol;
   for (int i = last_idx + 1; i < n; ++i)
      if (A[i] > A[last_idx]) last_idx = i;

   last_idx = idx[sz-1];
   while (true) {
      sol.push_back(A[last_idx]);
      last_idx = Par[last_idx];
      if (last_idx == -1) break;
   }

   reverse(sol.begin(), sol.end());
   for (int v : sol) cout << v << '\n';
}

signed main() {
   IOS; PREC;
   LIS();

   return EXIT_SUCCESS;
}

