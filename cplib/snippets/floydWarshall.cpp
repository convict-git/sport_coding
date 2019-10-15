#include <bits/stdc++.h>
using namespace std;

long long W[N][N];
void floydWarshall () {
   for (int k = 0; k < n; ++k)
      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            if (W[i][k] < inf && W[k][j] < inf)
               W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
}
