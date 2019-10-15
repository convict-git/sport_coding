#include <bits/stdc++.h>
#define er(x, y) cout<<x<<" "<<y
using namespace std;

int main(int argc, char *argv[]){
	int n, a, b, c, _mx, _mn=INT_MAX;
	cin >> n >> a >> b; _mx = b-a;
	while(n-2!=0){
		c=b-a;a=b;cin >> b;n-=1;
		if(_mn>c+b-a) _mn=c+b-a; else if(_mx<b-a) _mx=b-a;
	}_mn>_mx ? er(_mn,endl):er(_mx,endl);
}