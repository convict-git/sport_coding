#include <bits/stdc++.h>
#define fr(i,x,y) for (int i = x; i <= y; i++)
using namespace std;

int main(int argc, char *argv[]){
	int n; cin >> n; assert(n <= 1e3);
	int a[2893], c=-1;
	fr(i,1,9) a[++c] = i;
	fr(i,1,9) fr(j,0,9){ a[++c] = i; a[++c] = j;}
	fr(i,1,9) fr(j,0,9) fr(k,0,9){ 
		a[++c] = i; a[++c] = j; a[++c] = k;}
	a[++c] = 1; fr(i,1,3) a[++c] = 0;
	cout << a[n-1] << endl;
	return 0;
}