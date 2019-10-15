/*author* Priyanshu Shrivastav
 *_ __ ___  _ __ ___ ___  _ ____   ___  ___| |_ 
 | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __|
 | | | | | | | | (_| (_) | | | \ V /| | (__| |_ 
 |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__|
 When I wrote this, only God and I understood what I was doing
    * Now, God only knows*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define se second
#define fi first
#define ll long long
#define fr(x,y,z) for(auto x=y;x!=z;++x)
#define fo(n) for(ll i=0;i<n;i++)
#define all(v) v.begin(),v.end()
#define vit vector<int>::iterator it
#define sit set<int>::iterator it
#define e(x) cout<<x<<" "
#define er(x, y) cout<<x<<" "<<y<<endl
#define eR(x, y, z) cout<<x<<" "<<y<<" "<<z<<endl
#define y(x); {e(x)<<endl; return 0;}
using namespace std;

void pV(vector<int>*v){vit;fr(it,v->begin(),v->end())e(*it);e(endl);}
void pS(set<int>* s){sit;fr(it,s->begin(),s->end())e(*it);e(endl);} 
int gcd(int a,int b){int t,x,y;x=max(a,b);y=min(a,b);while(y!=0){t=x;x=y;y=t%y;}return x;} 
int lcm(int a,int b){ return(a*b)/gcd(a,b);}
int start_s=clock();
void timer(){int stop_s=clock();cout<<"time taken: "<<(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000<<endl;}

int main(int argc, char *argv[]){
	char c, d;
	int m1, m2, n1, n2, x, y, mx, mn;
	cin >> c >> n1 >> d >> n2;
	n1 = 8-n1, n2 = 8-n2, m1 = (int)(c-'a'), m2 = (int)(d-'a');
	x = m2-m1, y = n2-n1, mx=max(abs(x), abs(y)), mn = min(abs(x),abs(y));
	cout << mx << "\n";

	fo(mn) cout << (x > 0 ? 'R':'L') << (y > 0 ? 'D':'U') << "\n";
	fo(abs(x)-mn) cout << (x > 0 ? 'R':'L') << "\n";
	fo(abs(y)-mn) cout << (y > 0 ? 'D':'U') << "\n";
	//Beware no shit stuff here!
}
/*it was hard to write, so it should be hard to read!*/