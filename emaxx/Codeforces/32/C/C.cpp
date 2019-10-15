#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;

inline long long cal (int k, int s) {
   if (k % s == 0) return 1ll * (k/s) * s;
   else if (k/s != 0) return 1ll * ((k/s) + 1) * (k % s);
   else return 1ll * k;
}

int n, m, s;
signed main() {
   IOS; PREC;
   while (cin >> n >> m >> s) {
      cout << cal (n, s) * cal (m, s) << "\n";
   }
   return EXIT_SUCCESS;
}

