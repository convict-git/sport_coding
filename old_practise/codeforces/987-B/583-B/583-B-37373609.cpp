/*
	 Mon Apr 16 16:58:57 IST 2018
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

int n, *A, N = INT_MAX;

void rev(int *a, int*b){
	int p = 0, t;
	while (a+p != a+(b-a)/2){
		t = *(a+p);
		*(a+p) = *(b-1-p);
		*(b-1-p) = t;
		p+=1;
	}
}

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifdef CONVICTION
	freopen("in", "rt", stdin);
	int start_s=clock();
#endif

	int c = 0, p = 0;
	cin >> n;
	A = (int*) malloc(sizeof(int)*n);
	fo(n) cin >> A[i];

	while (c!=n){
		fo(n)
			if (A[i] <= c){
					A[i] = N;
					c+=1;
			}
		rev(A, A+n);
		if (c!=n) p+=1;
	}
	cout << p << "\n";

#ifdef CONVICTION
	double t = ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000;
	if (t > 1) cout << "Time Limit exceeded!\n";
	else cerr << "\ntime taken: " << t << " s\n";
#endif
	return 0;
	//Beware no shit stuff here!
}