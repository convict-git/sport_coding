/*
Sat Apr 28 13:24:32 IST 2018
*author* Priyanshu Shrivastav 
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

int n, d, *A;

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifdef CONVICTION
	freopen("in", "rt", stdin);
	int start_s=clock();
#endif

	int m = 0;
	cin >> n >> d;
	A = (int*) malloc(sizeof(int)*n);
	fo(n) cin >> A[i];
	sort(A, A+n);
	fr(i, 0, n-1) fr(j, i+1, n)
		if (A[j] - A[i] <= d) 
			j-i+1 > m ? m = j-i+1: m;
	m != 0 ? cout << n - m : cout << n-m-1;

#ifdef CONVICTION
	double Tt = ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000;
	if (Tt > 1) cout << "Time Limit exceeded!\n";
	else cerr << "\ntime taken: " << Tt << " s\n";
#endif
	return 0;
	//Beware no shit stuff here!
}