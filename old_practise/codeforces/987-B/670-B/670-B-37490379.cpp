/*author: mr.convict
 * Priyanshu Shrivastav
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n, k, *A, j;
int main(){
	cin >> n >> k;
	A = (ll*) malloc(sizeof(ll)*n);
	for (int i = 0; i < n; i++) cin >> A[i];

	k*=2, j = 1;
	while (j*(j+1) < k) j++;
	j-=1;
	k/=2;
	k-= j*(j+1)/2;
	cout << A[k-1] << '\n'; 
	return 0;
}