#include <bits/stdc++.h>
using namespace std;

int n, *A, N = INT_MAX;
int main(){
	cin >> n;
	A = (int*) malloc(sizeof(int)*n);
	for (int i = 0; i < n; i++) cin >> A[i];
	sort(A, A+n);

	int i = 0, c = 0, p = 0, m;
	while(i != n-1){
		m = A[i], A[i] = N, p+=1;
		for (int j = i+1; j < n; j++)
			if (A[j] > m && A[j] != N) 
				m = A[j], A[j] = N, p+=1, c+=1;
		while (A[i] == N) i++;
		if (p == n) break;
	}
	cout << c << "\n";
}