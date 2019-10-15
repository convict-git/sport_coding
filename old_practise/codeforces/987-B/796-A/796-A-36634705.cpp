#include <bits/stdc++.h>
#define fr(x,y,z) for(auto x=y;x!=z;x++)
#define er(x, y) cout<<x<<" "<<y
using namespace std;

int main(int argc, char *argv[]){
	int n,m,k,ai,p=INT_MAX;
	cin>>n>>m>>k;
	fr(i,0,n){cin>>ai;if(k>=ai && ai!=0 && p> abs(i+1-m))p=abs(i+1-m);}
	er(p*10,endl);
}