#include         <iostream>
#include         <iomanip>
#include         <functional>
#include         <algorithm>
#include         <unordered_map>
#include         <vector>
#include         <map>
#include         <set>
#include         <chrono>
#include         <queue>
#include         <random>
#include         <string>
#include         <cstring>
#include         <climits>
#include         <cstdlib>
#include         <cmath>
#include         <iomanip>
#include         <cassert>
#define x        first
#define y        second

#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
template<class T> bool nax(T& a, T b){return a < b ? (a = b, 1) : 0;}
template<class T> bool nix(T& a, T b){return a > b ? (a = b, 1) : 0;}
using namespace std;

struct polyhash {
   using ull = unsigned long long;
   using ll = long long;

   static const int Mod = int(1e9 + 123);
   static vector <int> pow1;
   static vector <ull> pow2;
   static int base;

   static int gen_base(const int before, const int after) {
      auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
      mt19937 mt_rand(seed);
      int base = uniform_int_distribution<int> (before + 1, after)(mt_rand);
      return base % 2 == 0 ? base - 1 : base;
   }

   vector <int> pref1;                     //hash prefix modulo Mod
   vector <ull> pref2;                     //hash prefix modulo 2^64

   polyhash (const string& s)
      : pref1(s.size(), 0)
        , pref2(s.size(), 0)
   {
      assert (base < Mod);
      const int n = int(s.size());
      while ((int)pow1.size() <= n) {    //storing for max possible string
         pow1.push_back(int(1LL * pow1.back() * base) % Mod);
         pow2.push_back(pow2.back() * base);
      }
      //pref[i] excludes i
      for (int i = 0; i < n; ++i) {
         pref1[i + 1] = int((pref1[i] + 1LL * s[i] * pow1[i]) % Mod);
         pref2[i + 1] = pref2[i] + 1LL * s[i] * pow2[i];
      }
   }
   //EXAMPLE :  if (hash_a(i, len, sz) == hash_b(j, len, sz))
   inline pair <int, ull> operator() (const int pos, const int len,
         const int mxPow = 0) const {
      int hash1 = (pref1[pos + len] - pref1[pos] + Mod) % Mod;
      ull hash2 = pref2[pos + len] - pref2[pos];
      if (mxPow != 0) {
         hash1 = int((1LL * hash1 * pow1[mxPow - (pos + len - 1)]) % Mod);
         hash2 *= pow2[mxPow - (pos + len - 1)];
      }
      return make_pair (hash1, hash2);
   }
};

int polyhash::base = polyhash::gen_base(256, polyhash::Mod);
///int polyhash::base = 31;

signed main() {

   return EXIT_SUCCESS;
}

