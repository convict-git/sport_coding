// sqrt decomposition library for range sum and update in O(root(N)) query and updates
// and O(N) preprocessing
// This library is created by Priyanshu Shrivastav (mr.convict)
// https://github.com/convict-git/sport_coding/blob/master/cplib/snippets/graph.cpp

#include      <bits/stdc++.h>
using namespace std;

class sqrt_root_decomp {
  public:
   const int S = 1000;
   int n;
   vector <int> B, A;

   sqrt_root_decomp (int n_, vector <int> a) {
      n = n_;
      A.assign(n, 0);
      B.assign(n/S + 1, 0);
      for (int i = 0; i < n; ++i) {
         A[i] = a[i];
         B[i/S] += a[i];
      }
   }

   int get_sum (int x, int y) {
      int l = x % S ? x/S + 1 : x/S;
      int r =  y % S ? y/S - 1 : y/S;

      int sm = 0;
      for (int i = x; i <= l*S - 1; ++i) sm += A[i];
      for (int i = l; i <= r; ++i) sm += B[i];
      for (int i = r*S + 1; i <= y; ++i) sm += A[i];
      return sm;
   }

   void update (int x, int y, int val) {
      int l = x % S ? x/S + 1 : x/S;
      int r =  y % S ? y/S - 1 : y/S;

      for (int i = x; i <= l*S - 1; ++i) A[i] += val;
      for (int i = l; i <= r; ++i) B[i] += S*val;
      for (int i = r*S + 1; i <= y; ++i) A[i] += val;
   }
};
