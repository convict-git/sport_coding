#include <bits/stdc++.h>
using namespace std;
typedef vector <int> vi;
typedef long long ll;

int t, n, counter;
ll sum = 0;
vi a;

int main(){
   ios_base::sync_with_stdio(false);
   cin.tie(nullptr);
   //freopen("in.txt", "r", stdin);
   //freopen("out.txt", "w", stdout);
   cin >> t;
   while(t--){
      cin >> n;
      a.resize(n);
      for(int i =0; i<n; i++) cin >> a[i];
      sum = 0;
      counter = 0;
      for(int i=0; i<n-1; i++){
         if(sum + a[i] < a[i+1]) {
            sum += a[i];
            counter++;
         }
      }
      if(n > 1) counter++;
      cout << counter << endl;
   }
}
