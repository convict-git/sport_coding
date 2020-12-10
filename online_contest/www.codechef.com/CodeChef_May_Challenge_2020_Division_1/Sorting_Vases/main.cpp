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

void preproc() {
}

void solve() {
   // N = 18, M = 18 // bitmask dp on graphs
   // atmost N - 1 swaps, can it be more,
   // No ? let a + b = N, a - 1 + b - 1 = N - 2 < N - 1
   // Hence to min no of swaps, increase number of cycles as much as possible
   // some disjoint cycles for p = [2 3 1 5 4]
   // (1 2 3) (4 5), 2 swaps + 1 swap
   // given free swaps (2 5), (1 3), (3 4)
   // use one free swap within the cycle (always useful) // free swaps left (2 5), (3 4) , and (1) (2 3) (4 5) or (3) (1 2) (4 5)
   // this requires? 2 swaps? 1 | 3 2 5 4
   //
   // we will think about the other approach as well
   // Editorial says :
   // i) robot operation's graph g, vertices are pos and edges are free moves
   // ii) freely permute elements in a connected component
   // iii) min swaps required manually to bring each element to it's actual component is the answer
   // iv)
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
