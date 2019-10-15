#include <iostream>
using namespace std;

void solve (int arr[], int n) {
   int l = 0, h = n - 1;
   int g;
   while (l <= h) {
      g = (l + h) / 2;
      cout << "g = " << g << "\n";
      if ((g - 1 - l + 1) % 2 == 0) { // even subarrays
         cout << "even subarrays\n";
         if (g - 1 >= 0 and arr[g] == arr[g - 1]) {
            h = g - 2;
            cout << "h became = " << h << "\n";

         }
         else if (g + 1 < n && arr[g] == arr[g + 1]) {
            l = g + 2;
            cout << "l became = " << l << "\n";
         }
         else break;
      }
      else { // odd subarrays
         cout << "odd subarrays\n";
         if (g - 1 >= 0 and arr[g] == arr[g - 1]) {
            l = g + 1;
            cout << "l became = " << l << "\n";
         }
         else if (g + 1 < n && arr[g] == arr[g + 1]) {
            h = g - 1;
            cout << "h became = " << h << "\n";
         }
         else break;
      }
   }
   cout << arr[g];
   return;
}

int main () {
   int n;
   cin >> n;
   int arr[n];
   for (int i = 0; i < n; i++)
      cin >> arr[i];
   solve(arr, n);
}
