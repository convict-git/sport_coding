#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int N = (int)1e7 + 10;
ll arr[N];

pair<ll*,  ll> fun(int start, int end){
  int sz = end - start + 1;
  ll* out, *arr1, *arr2;
  out = (ll*) malloc(sz * sizeof(long long));
  int out_idx = 0, arr1sz, arr2sz;
  if(end == start) {
    out[out_idx++] = arr[start];
    return {out, 0};
  }

  int mid = (start + end)/2;
  pair<ll* , ll> p1, p2;
  p1 = fun(start, mid);
  p2 = fun(mid+1, end);
  ll ans = p1.second + p2.second;
  arr1 = p1.first;
  arr1sz = mid - start + 1;
  arr2 = p2.first;
  arr2sz = end - (mid + 1) + 1;

  int i=0, j=0;

  while(i<arr1sz && j < arr2sz){
    if(arr2[j] > arr1[i]){
      out[out_idx++] = arr1[i++];
      continue;
    }
    if(arr2[j] < arr1[i]){
      ans += arr1sz - i;
      out[out_idx++] = arr2[j++];
      continue;
    }
  }
  while(i<arr1sz){
    out[out_idx++] = arr1[i++];
  }
  while(j<arr2sz){
    out[out_idx++] = arr2[j++];
  }
  free(arr1), free(arr2);
  return {out, ans};
}

int main() {
  int tc;
  scanf ("%i", &tc);
  while (tc--){
    int n;
    scanf("%i", &n);
    for (int i = 0; i < n; ++i)  {
      scanf("%lld", &arr[i]);
    }
    printf("%lld\n", fun(0, n - 1).second);
  }
}

