#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;

int giveRand (const int low, const int high) {
   auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
   mt19937 mt_rand(seed);
   return uniform_int_distribution<int> (low, high)(mt_rand); //closed interval [low, high]
}

signed main(int argc, char* argv[]) {
   srand(atoi(argv[1]));

   int n = giveRand(5, 10);
   cout << n << '\n';
   for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < n; ++j) {
         cout << giveRand(0, 1);
      }
      cout << '\n';
   }

   return EXIT_SUCCESS;
}

