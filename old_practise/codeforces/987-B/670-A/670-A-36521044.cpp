#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
	int n; cin >> n; assert(n>=1 && n<=1e6);
	int i = n%7 == 6 ? 1:0;
	cout << 2*(n/7) + i << " " << 2*(n/7) + min(2, n%7) << endl;
	return 0;
}