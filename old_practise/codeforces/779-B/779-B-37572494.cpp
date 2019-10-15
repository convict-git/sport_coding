/*
Tue Apr 24 23:00:08 IST 2018
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

string s;
int k;

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

#ifdef CONVICTION
	freopen("in", "rt", stdin);
	int start_s=clock();
#endif
	cin >> s >> k;
	int p = 0, q;

	for (int i = (int)s.size() - 1; i >= 0; i--)
		if((int)(s[i] - '0') == 0) p+=1, q = i;

	if (p == k) {
		p = 0;
		fr(i, q, (int)s.size()){
			if((int)(s[i] - '0') != 0) p+=1;
		}
		cout << p << '\n';

	}
	else if (p < k) cout << s.size() - 1 << '\n';
	else if (p > k){
		int r = 0;
		for (int i = (int)s.size()-1; i >= 0; i--){
			if((int)(s[i] - '0') == 0 && k !=0){
				k-=1;
			}
			else if((int)(s[i] - '0') != 0 && k !=0) r+=1; 
		}
		cout << r << '\n';
	} 

#ifdef CONVICTION
	double Tt = ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000;
	if (Tt > 1) cout << "Time Limit exceeded!\n";
	else cerr << "\ntime taken: " << Tt << " s\n";
#endif
	return 0;
	//Beware no shit stuff here!
}