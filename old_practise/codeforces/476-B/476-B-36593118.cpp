/*author* Priyanshu Shrivastav
 *_ __ ___  _ __ ___ ___  _ ____   ___  ___| |_ 
 | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __|
 | | | | | | | | (_| (_) | | | \ V /| | (__| |_ 
 |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__|
 When I wrote this, only God and I understood what I was doing
 * Now, God only knows*/

#include <bits/stdc++.h>
#define fr(x,y,z) for(auto x=y;x!=z;++x)
#define all(v) v.begin(),v.end()
#define vit vector<int>::iterator it
#define sit set<int>::iterator it
#define pb push_back
#define se second
#define fi first
#define ll long long
#define e(x) cout<<x<<" "
#define er(x, y) cout<<x<<" "<<y<<endl
#define eR(x, y, z) cout<<x<<" "<<y<<" "<<z<<endl
using namespace std;

void pV(vector<int>*v){vit;fr(it,v->begin(),v->end())e(*it);e(endl);}
void pS(set<int>* s){sit;fr(it,s->begin(),s->end())e(*it);e(endl);} 
int gcd(int a,int b){int t,x,y;x=max(a,b);y=min(a,b);while(y!=0){t=x;x=y;y=t%y;}return x;} 
int f(int n){int x=1,y=2; if (n==0)return 1;while(--n){x*=y; y+=1;} return x;}
int lcm(int a,int b){ return(a*b)/gcd(a,b);}
int start_s=clock();
void timer(){int stop_s=clock();cout<<"time taken: "<<(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000<<endl;}

int main(int argc, char *argv[]){
	int p=0, q=0, r=0, s,t, u, c=0;
	string s1, s2; cin >> s1 >> s2;
	fr(i,0,s1.size()){if(s1[i] == '+') p+=1; else p-=1;}
	fr(i,0,s2.size()) {if(s2[i] == '+') q+=1; else if(s2[i]=='-')q-=1;else r++;}
	s = p - q; t = r+1; u = r; if(r==0){p==q? e(1):e(0); return 0;}
	while(t>0){
		if (s+r==0 || s-r==0) u==2*(t-1) ? c+=2*f(u)/(f(u+1-t)*f(t-1)): c+=f(u)/(f(u+1-t)*f(t-1));
		t-=1;r-=2;}
	printf("%.9f\n", (double)c/pow(2,u+1));
}
/*it was hard to write, so it should be hard to read!*/