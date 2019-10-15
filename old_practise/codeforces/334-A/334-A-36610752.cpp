#include <bits/stdc++.h>
#define e(x,y) cout<<x<<" "<<y
using namespace std;
int main(){int n; cin >> n;assert(n%2==0);int m = pow(n,2)/2;
	for (int i = 0;i < pow(n,2)/2;i++)
	{e(i+1,pow(n,2)-i)<<" "; if ((i+1)%(n/2)==0)cout<<endl;}
}