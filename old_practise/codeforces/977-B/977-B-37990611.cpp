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
#define pii pair <int, int>
#define vi vector <int>
#define forn(i, j, k) for (int i = j; i < (int)k; i++)
#define forN(i, j, k) for (int i = k-1; i >= j; i--)
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define err(x) cerr << #x << " = " << x << ' '
#define mod(x) ((x)%N)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;

template <typename T> T gcd(T a, T b){if(b > a) swap(a, b); return b ? gcd <T> (b,a%b):a;}
template <typename T> T lcm(T a,T b){return(a*b)/gcd<T>(a,b);}
template <typename T> T son(T n){int k=1; while(n/(T)pow(10,k) != 0) k+=1; return k;} 

const ui N = 1000000009;
int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#ifdef CONVICTION
	freopen("in", "rt", stdin);
	int start_s=clock();
#endif
	int n, m = INT_MIN, c = 0;
	char c1, c2, a1, a2;
	cin >> n;
	vector <string> s;
	s.resize(n-1);
	forn(i, 0, n-1) s[i] = "";

	cin >> c1 >> c2; s[0]+=c1; s[0]+=c2;
	forn(i, 0, n-2){
		cin >> c1; s[i+1]+=c2; s[i+1]+=c1;
		c2 = c1;
	}
	sort(all(s));
	a1 = s[0][0], a2 = s[0][1];
	forn(i, 1, n-1){
		if (a1 == s[i][0] && a2 == s[i][1]) c+=1;
		else {
			c = 0, a1 = s[i][0], a2 = s[i][1];
		}
		if (c > m){ m = c, c1=a1, c2=a2;}
	}
	cout << c1 << c2 << '\n'; 
#ifdef CONVICTION
cerr << "\ntime taken: " << ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";
#endif
//Beware no shit stuff here!
	return 0;
}