#pragma GCC      optimize ("Ofast")
#include         <bits/stdc++.h>
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;

int giveRand (const int low, const int high) {
   auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
   mt19937 mt_rand(seed);
   return uniform_int_distribution<int> (low, high)(mt_rand);
}

int main(int argc, char* argv[]) {
   IOS; PREC;
   int tc = giveRand(1, 100);
   while (tc--) {
      int h = giveRand(1, 50);
      int w = giveRand(1, 50);

      cout << h << ' ' << w << '\n';
      for (int r = 0; r < h; ++r) {
         string s = "";
         for (int c = 0; c < w; ++c) {
            s += char('A' + giveRand(0, 25));
         }
         cout << s << '\n';
      }
   }
   cout << 0 << ' ' << 0 << '\n';
   return EXIT_SUCCESS;
}
