#include <bits/stdc++.h>
#define fr(x,y,z) for(auto x=y;x!=z;x++)
#define er(x, y) cout<<x<<" "<<y
using namespace std;

int main(int argc, char *argv[]){
	int t, s, x; cin >> t >> s >> x;
	if(t>x){er("NO",endl);return 0;} 
	if((x-t)%s==0 || ((x-t-1)%s==0 && x-t!=1)){er("YES",endl);return 0;}
	er("NO",endl);
}