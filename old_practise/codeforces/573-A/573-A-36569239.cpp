#include <bits/stdc++.h>
#define fr(x,y,z) for(auto x=y;x!=z;x++)
#define e(x) cout<<x<<endl;
#define ll long long int 
using namespace std;

ll gcd(ll a,ll b){ll t,x,y;x=max(a,b);y=min(a,b);while(y!=0){t=x;x=y;y=t%y;}return x;} 
ll lcm(ll a,ll b){return(a*b)/gcd(a,b);}

int log(ll a, ll b){
	ll n = lcm(a,b)/a;
	while(1){if(n==1) return 1;
		else if(n%2 == 0) n/=2;else if(n%3 == 0) n/=3;
		else return 0; }
}
int main(int argc, char *argv[]){
	ll q, r; int n, i=0;
	cin >> n >> q;
	while(i<n-1){cin >> r;
		if (log(q,r)==1 && log(r,q)==1) i+=1;
		else{e("No");return 0;}
		q = r;
	}e("Yes");return 0;
}