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


//fix the rows, find valid permutation for cols
//
int queens_n(int n) {
   vector <int> col_perm;
   int sol = 0;
   for (int i = 0; i < n; ++i) col_perm.push_back(i);

   while (next_permutation(col_perm.begin(), col_perm.end())) {
      bool works = true;
      for (int i = 0; i < n && works; ++i) {
         for (int j = i + 1; j < n && works; ++j) {
            if (abs(j - i) == abs(col_perm[i] - col_perm[j]))
               works = false;
         }
      }
      if (works) {
         ++sol;
//          cout << "new solution\n";
//          for (int i = 0; i < n; ++i) {
//             for (int j = 0; j < n; ++j) {
//                if (j == col_perm[i])
//                   cout << "| *" << (j == n - 1 ? " |" : " ");
//                else cout << "|  " << (j == n - 1 ? " |" : " ");
//             }
//             cout << '\n';
//          }
//          cout << '\n';
//          cout.flush();
      }
   }
   return sol;
}

signed main() {
   IOS; PREC;
   for (int i = 0; i < 13; ++i)
      cout << i << ' ' << queens_n(i) << "\n";

   return EXIT_SUCCESS;
}


