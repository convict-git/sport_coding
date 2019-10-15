#include <bits/stdc++.h>

using namespace std;


int main()
{
#ifdef CONVICTION
   if (!freopen ("in", "r", stdin)) return -1;
#endif
   int q;
   scanf("%d",&q);
   while(q--)
   {
      int n,k, c = 0;
      scanf("%d%d",&n,&k);
      int *arr = new int[n];
      for(int i=0;i<n;++i)
         scanf("%d",arr+i);
      sort(arr,arr+n);
      for (int i = 0; i < n; ++i)
         if (arr[i] <= k) ++c;


      for(int i = c; c < n - 1; ++i)
      {
         if(arr[i] > k && i < n - 1)
         {
            --arr [i];
            --arr [i + 1];
            if(arr [i] == k) ++c;
            if(arr [i + 1] == k) ++c;
         }
         if (i == n - 2) {
            i = c; //imp
            sort (arr, arr + n);
        }
         if (c == n - 2) break;
      }
      long int sum=0;
      for(int i=0;i<n;++i)
      {
         sum += arr[i];
      }
      printf("%ld\n",sum);
   }
   return 0;
}

