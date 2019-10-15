#include <bits/stdc++.h>
#define fr(x,y,z) for(auto x=y;x<=z;x+=2)
#define er(x, y) cout<<x<<" "<<y
using namespace std;

int main(int argc, char *argv[]){
	int n; cin >> n; if(n%2!=0){er(-1,endl);return 0;}
	fr(i,2,n+1)er(i,i-1)<<" ";
}
