#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]){
	long long int r, x, y, x1, y1, a, p, q;
	cin >> r >> x >> y >> x1 >> y1;
	long double d = sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1)); q = ceil(d);
	q%r == 0 ? a = q/r : a = q/r + 1;
	p = a%2==0 ? p = a/2 : (a+1)/2; cout << p << endl;
	return 0;
}