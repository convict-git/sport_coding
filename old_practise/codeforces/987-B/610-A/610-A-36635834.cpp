#include <bits/stdc++.h>
#define er(x, y) cout<<x<<" "<<y
using namespace std;
int main(int argc, char *argv[]){int n; cin >> n;
	if(n%2!=0){er(0,endl); return 0;}
	n%4==0 ? er(n/4-1,endl):er(n/4,endl);}