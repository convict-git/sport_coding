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
#define fr(x,y,z) for(auto x=y;x!=z;++x)
#define fR(x,y,z) for(auto x=z;x>=y;x--)
#define fo(n) fr(i,0,n)
#define fm(m,n) fr(i,0,m) fr(j,0,n)
#define all(v) v.begin(),v.end()
#define vit vector<int>::iterator it
#define sit set<int>::iterator it
#define e(x) cout<<x<<" "
#define er(x, y) cout<<x<<" "<<y<<endl
#define eR(x, y, z) cout<<x<<" "<<y<<" "<<z<<endl
#define R(x,y) {er(x,y); return 0;}
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;

template <typename T> void pV(const vector<T> &v) {for(auto &it:v)e(it)<<endl;} 
template <typename T> void pS(const set<T> &s) {for(auto&it:s)e(it)<<endl;}
template <typename T> T gcd(T &a, T &b){T t,x,y; x = max(a,b); y=min(a,b); while(y!=0){t=x; x=y; y=t%y;} return x;}
template <typename T> T lcm(T &a,T &b){return(a*b)/gcd<T>(a,b);}

int start_s=clock();
void timer(){int stop_s=clock();er("time taken: ",(stop_s-start_s)/double(CLOCKS_PER_SEC)*1000);}

int main(int argc, char *argv[]){
	int a[5], c[5]={0}, q=0, s=0;
	fo(5) cin >> a[i], s+=a[i]; sort(a, a+5);
	fR(j, 0, 4){q = 0; fR(i,0, 4){if (a[i] == a[j]) q!= 3 ? q+=1 : q;} if(q >=2) c[j] = q*a[j];}
	sort(c, c+5);
	e(s-c[4])<<endl;

	//Beware no shit stuff here!
}
///*it was hard to write, so it should be hard to read!*/