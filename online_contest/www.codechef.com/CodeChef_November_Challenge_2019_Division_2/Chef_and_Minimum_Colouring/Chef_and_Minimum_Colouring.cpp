#include <bits/stdc++.h>
using namespace std;

int main() {
   int tc;
   cin >> tc;
   while (tc--) {
     int n, m;
     cin >> n >> m;
     vector<pair<int,int>> A(n);

     for (int i = 0; i < n; ++i)
       cin >> A[i].first, A[i].second = i % m;

     sort (A.begin(), A.end());

     vector <int> fq(m);
     int cnt = 0;

     int i = 0, j = 0;
     int mn = INT_MAX;

     int last_j = -1;

     for (; i < n; ++i) {  // first pointer
       j = max(i, j);
       for(; j < n && cnt < m;) { // second pointer
         if (last_j != j) {
           if (fq[A[j].second] == 0) {
             ++cnt;
           }
           ++fq[A[j].second];
         }
         if (cnt == m) {
           break;
         }
         ++j;
       }
       last_j = j;
       if (cnt == m && i != j) {
         mn = min(mn, A[j].first - A[i].first);
       }

       --fq[A[i].second];
       if (fq[A[i].second] == 0) --cnt;
     }
     cout << mn << '\n';
   }
   return 0;
}

