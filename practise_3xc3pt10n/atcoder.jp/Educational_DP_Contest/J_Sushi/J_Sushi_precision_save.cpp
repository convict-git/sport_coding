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
using ff = long double;
using pii = pair<int,int>;

#define debug(args...) { \
/* WARNING : do NOT compile this debug func calls with following flags: // \
 * // -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2*/ \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) { it->empty();
   cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << fixed << setprecision(15) << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

// let k = a + b + c
// E(a,b,c) := Expected no. of trials required to reach (0,0,0) from (a,b,c)
// E(a,b,c) = (n-k)/n * (1 + E(a,b,c)) + a/n * (1 + E(a-1,b,c)) + b/n * (1 + E(a+1,b-1,c)) + c/n * (1 + E(a,b+1,c-1))
// hence, E(a,b,c) = n/k + a/k * E(a-1,b,c) + b/k * E(a+1,b-1,c) + c/k * E(a,b+1,c-1)

const int N = 304;

ff E[N][N][N];
int n, cnt[3];

void solve() {
   E[0][0][0] = 0;

   for (int c = 0; c <= n; ++c) {
      for (int b = 0; b+c <= n; ++b) {
         for (int a = 0; a+b+c <= n; ++a) {
            if (a + b + c > n) continue;
            if (!a && !b && !c) continue;

            int k = a + b + c;

            E[a][b][c] = n;

            if (a) E[a][b][c] += E[a-1][b][c] * a;
            if (b) E[a][b][c] += E[a+1][b-1][c] * b;
            if (c) E[a][b][c] += E[a][b+1][c-1] * c;

            E[a][b][c] /= k;
         }
      }
   }
   cout << E[cnt[0]][cnt[1]][cnt[2]] << '\n';
}

signed main() {
   IOS; PREC;
   cin >> n;

   cnt[0] = cnt[1] = cnt[2] = 0;

   for (int i = 0, foo; i < n; ++i)
      cin >> foo, cnt[foo-1]++;

   solve();

   return EXIT_SUCCESS;
}

