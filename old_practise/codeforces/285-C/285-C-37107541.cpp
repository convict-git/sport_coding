/*author* Priyanshu Shrivastav
 *_ __ ___  _ __ ___ ___  _ ____   ___  ___| |_ 
 | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __|
 | | | | | | | | (_| (_) | | | \ V /| | (__| |_ 
 |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__|
 When I wrote this, only God and I understood what I was doing
 * Now, only God knows*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define se second
#define fi first
#define fr(x,y,z) for(auto x=y;x!=z;++x)
#define fo(n) for(int i=0;i<n;i++)
#define forn(i, x) for (int i=0;i<(int)n;i++)
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define vit vector<int>::iterator it
#define sit set<int>::iterator it
#define R(x); {cout << x << "\n"; return 0;}
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;

template <typename T> void pV(const vector<T> &v) {for(auto &it:v)e(it)<<endl;} 
template <typename T> void pS(const set<T> &s) {for(auto&it:s)e(it)<<endl;}
template <typename T> T gcd(T &a, T &b){T t,x,y; x = max(a,b); y=min(a,b); while(y!=0){t=x; x=y; y=t%y;} return x;}
template <typename T> T lcm(T &a,T &b){return(a*b)/gcd<T>(a,b);}
template <typename T> T son(T n){int k=1; while(n/(T)pow(10,k) != 0) k+=1; return k;} 

int start_s=clock();
void timer(){int stop_s=clock();cout << "time taken: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";}

int n;
ll *A;

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ll s = 0;
	cin >> n;
	A = (ll*) malloc(sizeof(ll)*n);

	fo(n) cin >> A[i];
	sort(A,A+n);
	fo(n) s+=abs(i+1 - A[i]);
	cout << s << "\n"; 
	//Beware no shit stuff here!
}