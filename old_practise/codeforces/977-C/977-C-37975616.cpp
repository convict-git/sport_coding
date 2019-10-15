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

int n, k, *A;
int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#ifdef CONVICTION
	freopen("in", "rt", stdin);
	int start_s=clock();
#endif
	int p = -1;
	cin >> n >> k;
	A = (int*) malloc(sizeof(int)*n);
	forn(i, 0, n) cin >> A[i];
	sort(A, A+n);
	forn(i, 0, n){
		i == n-1 || A[i] != A[i+1] ? p = i+1 : p;
		if(p == k) {cout << A[p-1]; break;}
		else if (k == 0) {
			if (A[0] >= 2) {cout << A[0]-1; break;}
			else {cout << -1; break;}
		}
		else if (p > k || k > n) {cout << -1; break;}
	}
	cout << '\n';
#ifdef CONVICTION
	int stop_s=clock(); cerr << "\ntime taken: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";
#endif
	//Beware no shit stuff here!
	return 0;
}