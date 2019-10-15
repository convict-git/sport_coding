#include <bits/stdc++.h>
#define fr(x,y,z) for(auto x=y;x!=z;x++)
#define er(x, y) cout<<x<<" "<<y
using namespace std;

int main(int argc, char *argv[]){
	string s; char c;
	int n=0;
	while((c=getchar()) && c!=EOF)if(c=='Q' || c=='A') s+=c;
	fr(i,0,s.size()) if(s[i]=='Q')fr(j,i+1,s.size())if(s[j]=='A')fr(k,j+1,s.size())if(s[k]=='Q')n+=1;
	er(n,endl);
}