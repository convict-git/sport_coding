#include <bits/stdc++.h>
using namespace std;

int main(){
	int n, x, p=0, ai, c=0; cin >> n >> x; 
	for (int i = 0; i < n; i++){cin >> ai; p+=ai;}
	while (abs(p) > x) {p>0 ? p-=x:p+=x; c+=1;}
	if (p == 0) cout << c << endl;
	else cout << ++c << endl;
	return 0;
}