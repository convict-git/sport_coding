/*author* Priyanshu Shrivastav
 * *from*(IIT Palakkad)
 *_ __ ___  _ __ ___ ___  _ ____   ___  ___| |_
 | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __|
 | | | | | | | | (_| (_) | | | \ V /| | (__| |_
 |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__|
 wHEN i WROTE THIS, ONLY gOD AND i UNDERSTOOD WHAT i WAS DOING
 * nOW, ONLY gOD KNOWS*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define se second
#define fi first
#define fr(x,y,z) for(auto x=y;x!=z;++x)
#define fo(n) for(int i=0;i<(int)n;i++)
#define forn(i, n) for (int i=0;i<(int)n;i++)
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define R(x); {cout << (x) << "\n"; return 0;}
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;

template <typename T> T gcd(T a, T b){T t,x,y; x = max(a,b); y=min(a,b); while(y!=0){t=x; x=y; y=t%y;} return x;}
template <typename T> T lcm(T a,T b){return(a*b)/gcd<T>(a,b);}
template <typename T> T son(T n){int k=1; while(n/(T)pow(10,k) != 0) k+=1; return k;}

ll n, *A, *B, *C, c1 = 0, c2 = 0;

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#ifdef CONVICTION
	int start_s=clock();
#endif

	int t;
	cin >> n;
	C = (ll*) malloc(sizeof(ll)*(n));
	A = (ll*) malloc(sizeof(ll)*(n+1));
	B = (ll*) malloc(sizeof(ll)*(n+1));
	A[0] = 0, B[0] = 0;
	fo(n) cin >> C[i];

	fr(i,1,n+1){
		c1+=C[i-1], c2+=C[n-i];
			A[i] = c1, B[i] = c2;
	}
	//fo(n+1) cout << A[i] << " " << B[i] << "\n";
	c1 = c2 = 0;
	while(c1 + c2 < n){
		A[c1] > B[c2] ? c2+=1 : c1+=1;
		if (A[c1] == B[c2]){
			if (c1 + c2 == n-1) c1+=1;
			else if (c1 + c2 < n-1) c1+=1, c2+=1;
		}
	}
	cout << c1 << " " << c2 << "\n";

#ifdef CONVICTION
	int stop_s=clock();
	cerr << "\ntime taken: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";
#endif
	return 0;
	//Beware no shit stuff here!
}
