#include <bits/stdc++.h>
using namespace std;

pair<vector<long long>, long long> fun(vector<long long> & arr, int start, int end){
  if(end == start){
    vector<long long> out;
    out.push_back(arr[start]);
    return make_pair(out, 0);
  }
  int mid = (start + end)/2;
  pair<vector<long long> , long long> p1, p2;
  p1 = fun(arr, start, mid);
  p2 = fun(arr, mid+1, end);
  long long ans = p1.second + p2.second;
  vector<long long> arr1, arr2, out;
  arr1 = p1.first;
  arr2 = p2.first;
  int i=0, j=0;
  while(i<arr1.size() && j < arr2.size()){
    if(arr2[j] > arr1[i]){
      out.push_back(arr1[i++]);
      continue;
    }
    if(arr2[j] < arr1[i]){
      ans += arr1.size() - i;
      out.push_back(arr2[j++]);
      continue;
    }
  }
  while(i<arr1.size()){
    out.push_back(arr1[i++]);
  }
  while(j<arr2.size()){
    out.push_back(arr2[j++]);
  }
  return make_pair(out, ans);
}

int main() {
  int tc;
  scanf ("%i", &tc);
  while (tc--){
    int n;
    scanf("%i", &n);
    vector <long long> ar(n);
    for (int i = 0; i < n; ++i)  {
      scanf("%lld", &ar[i]);
    }
    printf("%lld\n", fun(ar, 0, n - 1).second);
  }
}
