#include <bits/stdc++.h>
using namespace std;
template <typename T> int perm_idx(const T &s) { // O(n^2)
   int index = 0;
   int position = 2;
   int factor = 1;
   for (int p = (int) s.size() - 2; p >= 0; p--) {
      int successors = 0;
      for (int q = p + 1; q < (int) s.size() ; q++) {
         if (s[p] > s[q]) {
            successors++;
         }
      }
      index += (successors * factor);
      factor *= position;
      position++;
   }
   return index;
}
