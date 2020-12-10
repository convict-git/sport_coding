#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

#if __cplusplus > 201103L
seed_seq seq{
  (uint64_t) chrono::duration_cast<chrono::nanoseconds>
    (chrono::high_resolution_clock::now().time_since_epoch()).count(),
    (uint64_t) __builtin_ia32_rdtsc(),
    (uint64_t) (uintptr_t) make_unique<char>().get()
};
mt19937 rng(seq); //uniform_int_distribution<int> (l, h)(rng); //[low, high]
#else
auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rng(seed);
#endif

template <class T = int> T giveRand (const T& low, const T& high) {
   return uniform_int_distribution<T> (low, high)(rng); //closed interval [low, high]
}

void preproc() {
}

void solve() {
   int tc=10;
   cout << tc << '\n';
   while (tc--) {
      int n = 1e5;
      cout << n << ' ';
      vector <pair <int ,int>> edges;
      for (int i = 0; i < 1e4; ++i) {
         int u = giveRand(1, n-1), v = giveRand(u+1, n);
         edges.push_back({u, v});
      }
      cout << edges.size() << '\n';
      for (auto e : edges) {
         cout << e.first << ' ' << e.second << '\n';
      }
   }
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  // cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}

