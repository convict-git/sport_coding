#include <bits/stdc++.h>
using namespace std;

const int N = (int)1e4 + 100;

int t, n, K;
int arr[N];

void modify (int &a, int &b, int complete, int x) {
   int quo = complete % 3;
   int xorr = a ^ b;
   if (quo == 1) {
      b = a;
      a = xorr;
   }
   else if (quo == 2) {
      a = b;
      b = xorr;
   }
   if (x == 1) {
      int xorr_ = a ^ b;
      a = xorr_;
   }
}

int main() {
    cin >> t;
    int a, b, complete;
    int x = 0;
    while (t--) {
        cin >> n >> K;
        for (int i = 0; i < n; i++)
            cin >> arr[i];
        a = (n - 1)/2;
        b = (K % n) - 1;
        if (n & 1)
           a--;
        for (int i = 0; i <= a; i++) {
           complete = K / n;
           x = 0;
           if (i <= b and (n - i - 1) <= b)
              complete++;
           else if (i <= b and (n - i - 1) > b)
              x = 1;
           modify(arr[i], arr[n - i - 1], complete, x);
        }
        if (n & 1) {
           if (K > (n - 1)/2)
              arr[(n - 1)/2] = 0;
        }
        for (int i = 0; i < n; i++)
           cout << arr[i] << " ";
         cout << "\n";
    }
    return 0;
}
