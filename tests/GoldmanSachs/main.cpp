#include      <bits/stdc++.h>
using namespace std;
#pragma GCC   optimize ("Ofast")
#pragma GCC   optimize ("unroll-loops")
#pragma GCC   target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS   ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC  cout.precision (10); cout << fixed
#define x     first
#define y     second
#define bg(x) " [ " << #x << " : " << (x) << " ] "
#define un(x) sort(x.begin(), x.end()), \
              x.erase(unique(x.begin(), x.end()), x.end())
using   ll  = long long;
using   ff  = long double;
using   pii = pair<int,int>;
using   pil = pair<int,ll>;
/*****************************************************************************/

vector<int> findSpecialProduct(vector<int> inputArray) {
   int sz = (int)inputArray.size();
   vector <int> pref_mul(sz), suff_mul(sz), ans(sz);
   for (int i = 0; i < sz; ++i) {
      if (i == 0) {
         pref_mul[i] = inputArray[i];
      }
      else pref_mul[i] = pref_mul[i - 1] * inputArray[i];
   }
   for (int i = sz - 1; i >= 0; --i) {
      if (i == sz - 1) {
         suff_mul[i] = inputArray[i];
      }
      else suff_mul[i] = suff_mul[i + 1] * inputArray[i];
   }

   for (int i = 0; i < sz; ++i) {
      if (i == 0) {
         ans[i] = suff_mul[i + 1];
      }
      else if (i == sz - 1) {
         ans[i] = pref_mul[i - 1];
      }
      else {
         ans[i] = suff_mul[i + 1] * pref_mul[i - 1];
      }
   }
   return ans;
}

signed main() {
   IOS; PREC;

   return EXIT_SUCCESS;
}

