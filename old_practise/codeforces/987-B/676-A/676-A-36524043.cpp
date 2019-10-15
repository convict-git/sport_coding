#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
	int n, ai, a, b, f=0;
	cin >> n; assert(n >=2 && n <= 100);
	for (int i = 0 ;i < n; ++i){ cin >> ai; 
		if (ai == 1 || ai == n){
			if (f==0) {a=i+1; f=1;} else {b=i+1;break;}
		}
	} int x = (a-1) >= (n-b) ? b-1: n-a; cout << x << endl;
return 0;
}