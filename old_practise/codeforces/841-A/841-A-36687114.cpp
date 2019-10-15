#include <bits/stdc++.h>
#define fr(i,x,y) for(auto i=x;i!=y;++i)
#define all(x) x.begin(),x.end()
#define e(x) cout<<x
#define y(x) {e(x)<<endl; return 0;}
#define er(x,y) cout<<x<<y<<endl
#define ll long long 
using namespace std;
int main()
{
	unsigned int n,k,p=1; cin >> n >> k;
	string s; cin >> s; sort(all(s));
	char c=s[0]; 
	fr(i,1,n){ c==s[i] ? p+=1 : (c=s[i],p=1) ;if(p>k) y("NO")} y("YES")
}