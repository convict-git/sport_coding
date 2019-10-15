#include <bits/stdc++.h>
#define fr(x,y,z) for(auto i=y;i!=z;i++)
#define er(x, y) cout<<x<<" "<<y
#define t(x) pow(2,x)
using namespace std;

int main(int argc, char *argv[]){
	string s; cin >> s; int n = s.size(),c=0;
	if(n!=1)fr(i,0,n-1)c+=t(n-1-i);
	fr(i,1,n+1) if(s[i-1] == '7') c+=t(n-i); er(++c,endl); 
}