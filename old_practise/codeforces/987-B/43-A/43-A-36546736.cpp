#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]){
	int n, ai[2]={0};
	string a, b, c, ans;
	cin >> n;
	while(n) {n-=1;
		cin >> c;
		if (a=="\0") a = c; else if (b=="\0" && a!=c) b = c;
		if (c==a) ai[0]+=1; else if (c==b) ai[1]+=1;
		}
	ans = ai[0] > ai[1] ? a : b; cout << ans << endl;
	return 0;
}