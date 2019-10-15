#include <bits/stdc++.h>
#define fr(i,x,y) for(auto i=x;i!=y;++i)
#define e(x) cout<<x
#define y(x) {e(x)<<endl; return 0;}
using namespace std;
int main()
{
	int n, p=0, f=0, q=INT_MIN, _i, _a, _b; cin >> n; int a[n];
	fr(i,0,n) cin >> _a >> _b, a[i] = _a-_b, p+=(_a-_b), (_a>_b ? f+=1: f);
	if(f== 0 || f==n) y(0)
	fr(i,0,n) if(abs(p-2*a[i]) > q) _i=i, q = abs(p-2*a[i]); y(++_i)
}