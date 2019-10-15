/*
Thu Apr 19 13:05:39 IST 2018
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

ull a, b;
	
int main(int argc, char *argv[]){
	//ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifdef CONVICTION
	freopen("in", "rt", stdin);
	int start_s=clock();
#endif

	cin >> a >> b;
	if (b-a > 9) cout << 0 << "\n";
	else {
		int m, n, i = 0, s = 1;
		son <ull> (a) != 1 ? m = a - (a/10)*10: m = (int)a;
		son <ull> (b) != 1 ? n = b - (b/10)*10: n = (int)b;
		if (n >= m) while (i != n-m) s*=(n-i++);
		else {cout << 0 << "\n"; return 0;}
		cout << (son <int> (s) != 1 ? s-(s/10)*10 : s) << "\n";
} 
#ifdef CONVICTION
	double Tt = ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000;
	if (Tt > 1) cout << "Time Limit exceeded!\n";
	else cerr << "\ntime taken: " << Tt << " s\n";
#endif
	return 0;
	//Beware no shit stuff here!
}