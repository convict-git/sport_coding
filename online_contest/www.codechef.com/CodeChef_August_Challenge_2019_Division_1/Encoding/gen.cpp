#include      <bits/stdc++.h>
using namespace std;

template <class T = int> T giveRand (const T& low, const T& high) {
   auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
   mt19937 mt_rand(seed);
   return uniform_int_distribution<T> (low, high)(mt_rand); //closed interval [low, high]
}

int sz (long long n) {
   int k = 0;
   while (n) {
      ++k, n /= 10;
   }
   return k;
}

signed main() {
   int tc = 3;
   cout << tc << '\n';

   while (tc--) {
      int l = 1, h = (int)1e5;
      int L = giveRand(l, h);
      int R = giveRand(L, h + 1);
      cout << sz(L) << ' ' << L << '\n';
      cout << sz(R) << ' ' << R << "\n";
   }


   return EXIT_SUCCESS;
}

