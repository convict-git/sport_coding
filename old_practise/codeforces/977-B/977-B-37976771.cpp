/*author* Priyanshu Shrivastav 
*from*(IIT Palakkad)
 *_ __ ___  _ ______ ___  _ ____   ___  ___| |_ 
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
#define forn(i, j, k) for (int i = j; i < (int)k; i++)
#define forN(i, j, k) for (int i = k-1; i >= j; i--)
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define err(x) cerr << #x << " = " << x
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;

template <typename T> T gcd(T a, T b){if(b > a) swap(a, b); return b ? gcd <T> (b,a%b):a;}
template <typename T> T lcm(T a,T b){return(a*b)/gcd<T>(a,b);}
template <typename T> T son(T n){int k=1; while(n/(T)pow(10,k) != 0) k+=1; return k;} 

int n;
string s;
int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#ifdef CONVICTION
	freopen("in", "rt", stdin);
	int start_s=clock();
#endif

	cin >> n;
	cin >> s;
	int q = INT_MIN, p[n-1], pos;
	forn(i, 0, n-1) p[i] = 0;
	forn(i, 0, n-1) forn(j, 0, n-1) 
		if (s[i] == s[j] && s[i+1] == s[j+1]) 
			p[i]+=1;
	forn(i, 0, n-1)
		p[i] > q ? pos = i, q = p[i] : pos, q;
	cout << s[pos] << s[pos+1] << '\n';

#ifdef CONVICTION
cerr << "\ntime taken: " << ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";
#endif
//Beware no shit stuff here!
	return 0;
}