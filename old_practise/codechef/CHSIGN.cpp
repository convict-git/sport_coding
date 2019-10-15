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
#define neg(x) ((x) > 0 ? (x)*=-1 : (x))

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;

template <typename T> T gcd(T a, T b){if(b > a) swap(a, b); return b ? gcd <T> (b,a%b):a;}
template <typename T> T lcm(T a,T b){return(a*b)/gcd<T>(a,b);}
template <typename T> T son(T n){int k=1; while(n/(T)pow(10,k) != 0) k+=1; return k;} 

const ui N = 1000000007;
int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
#ifdef CONVICTION
	freopen("in", "rt", stdin);
	int start_s=clock();
#endif
	int t;
	cin >> t;
	while (t--){
		int n;
		cin >> n;
		ll A[n+2], B[2][n+2], C[n+2];
		vector <int> p, r;
		
		forn(i, 1, n+1) cin >> A[i], C[i] = A[i];
		C[n+1] = C[0] = A[n+1] = A[0] = INT_MAX;

		forn(i, 1, n+1)
			if ((C[i-1] > C[i]) && (C[i+1] > C[i])) p.pb(i);
		
		forn(i, 0, p.size()-1)
			if ((p[i+1] - p[i] == 2) && (C[p[i]] + C[p[i+1]] < C[p[i]+1]))
				r.pb(p[i]);
										
		forn(i, 0, p.size()-1){
			if (p[i+1] - p[i] == 2){
					int q = p[i], s, x;
					i++;
					while ((i != p.size()-1) && (p[i+1] - p[i] ==2))
						i++;
					s = p[i];

					B[0][q] = C[q], B[1][q] = 0;
					for (int j = q+2; j <= s; j+=2){
						if (binary_search(all(r), j-2)){
							B[0][j] = max(B[0][j-2], B[1][j-2]) + C[j];
							B[1][j] = B[0][j] - C[j];
						}
						else { 
							B[0][j] = B[1][j-2] + C[j];
							B[1][j] = max(B[0][j-2], B[1][j-2]);
						}
					} 
					x = (B[0][s] >= B[1][s] ? 0 : 1);
					for (int j = s; j > q; j-=2){
						if (x == 0){
							neg(A[j]);
							if (binary_search(all(r), j-2)){ 
								x = (B[0][j] == B[0][j-2] + C[j] ? 0 : 1);
							}
							else x = 1;
						}
						else x = (B[1][j] == B[0][j-2] ? 0 : 1);
					}
					x == 0 ? neg(A[q]) : A[q];
			}
		}
		forn(i, 0, p.size()-1){
			if (p[i+1] - p[i] > 2){
				if (i == 0 ) neg(A[p[i]]);
				else if (p[i] - p[i-1] > 2) neg(A[p[i]]);
				if (i == ((int)p.size()-2)) neg(A[p[i+1]]);
			} 
		}
		if ((int)p.size() == 1) neg(A[p[0]]);
		forn(i, 1, n+1) cout << A[i] << (i != n ? ' ' : '\n');
	}
#ifdef CONVICTION
cerr << "\ntime taken: " << ((int)clock()-start_s)/double(CLOCKS_PER_SEC)*1000 << " s\n";
#endif
	return 0;
}
