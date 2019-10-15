#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]){
	long long int r, x, y, x1, y1, a, p, q;
	cin >> r >> x >> y >> x1 >> y1;
	cout << ceil(sqrt((x-x1)*(x-x1) + (y-y1)*(y-y1))/(r*2.0)) << endl;
	return 0;
}