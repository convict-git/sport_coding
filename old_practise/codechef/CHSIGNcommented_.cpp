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
		ll A[n+2], B[2][n+2], C[n+2];//C will keep the orignal A and A will be changed
		vector <int> p, r;

		forn(i, 1, n+1) cin >> A[i], C[i] = A[i];
		C[n+1] = C[0] = A[n+1] = A[0] = INT_MAX;//for dips on edges

		forn(i, 1, n+1) //calculation dips
			if ((C[i-1] > C[i]) && (C[i+1] > C[i])) p.pb(i);//p stores the index of dips

		//forn(i, 0, p.size()) cout << i << ' '; cout << '\n';
		//cout << "p "; for (auto &it:p) cout << it << ' '; cout << '\n';
		//cout << "A[p] "; for (auto &it:p) cout << A[it] << ' '; cout << '\n';

		forn(i, 0, p.size()-1)
			if ((p[i+1] - p[i] == 2) && (C[p[i]] + C[p[i+1]] < C[p[i]+1]))
				r.pb(p[i]);/*r stores the index of the dip so that the current dip and next dip have sum
										 less than the element in the middle*/

		//cout << "r ";for (auto &it:r) cout << it << ' '; cout << '\n';

		/* I broke the problem into segments since I wanted max sum from dips
		 * * i)If the dips are alternative two cases
		 * * * a) the sum of the two alternative dips is greater than or equal to the element in the middle
		 * * * * so in this case I can only select one of the two dips to turn to negative else I won't be able to satisfy
		 * * * * strictly positive sum of contigous subsequene of length greater than 1.
		 * * * b) the sum of the two alternative dips is less than the element in the middle
		 * * * * so in this case I can select both the dips and turn them negative as even if I select a contigous subsequence
		 * * * * including all three elements it will turn up positive.
		 * * ii) if the dips are not alternative then I can select all of them
		 *
		 * So first I try to get subsequences with alternative dips as long as possible and select the dips which help me get the m
		 * maximum some out of them keeping in mind i) a) and i) b).(taking each subsequence one by one)
		 *
		 * and then all non alternative dips and turn them negative
		 */
		forn(i, 0, p.size()-1){
			if (p[i+1] - p[i] == 2){
					int q = p[i], s, x;
					i++;
					while ((i != p.size()-1) && (p[i+1] - p[i] ==2))
						i++;
					s = p[i];
					//cout << "q " << q << ' ' << "s "<< s << '\n';
					//q and s are the starting and ending indexes where alternative dips occurs


					//B[0][i] is the max sum of the dips until the ith index including the ith index
					//B[1][i] is the max sum of the dips until the ith index excluding the ith index

					B[0][q] = C[q], B[1][q] = 0;
					for (int j = q+2; j <= s; j+=2){
						if (binary_search(all(r), j-2)){/*if j-2(previous dip) is such that the sum of current dip and previous dip
																							is less than the element in the middle than I can include both together too*/
							B[0][j] = max(B[0][j-2], B[1][j-2]) + C[j];
							B[1][j] = B[0][j] - C[j];
						}
						else { /*else I have to select either of one*/
							B[0][j] = B[1][j-2] + C[j];
							B[1][j] = max(B[0][j-2], B[1][j-2]);
						}
					}
					//therefore max(B[0][s], B[1][s]) represents the max sum of the dips that can be achieved between q and s index

					//for (int j = q;j < s+1; j+=2) cout << B[0][j] << ' '; cout << '\n';
					//for (int j = q;j < s+1; j+=2) cout << B[1][j] << ' '; cout << '\n';

					//Now I will trace back in B to find which helped me get the max sum
					//x helps me to switch from B[0] to B[1] therefore x = {0, 1}
					//if while tracing back for some i, x = 0 that means A[i] was included to make the sum max
					//else if x = 1 means A[i] was excluded to make the sum max


					x = (B[0][s] >= B[1][s] ? 0 : 1);
					for (int j = s; j > q; j-=2){
						if (x == 0){
							neg(A[j]);
							if (binary_search(all(r), j-2)){ /*if j-2(previous dip) is such that the sum of current dip and previous dip
																							is less than the element in the middle than both are eligible to be turned negative*/
								x = (B[0][j] == B[0][j-2] + C[j] ? 0 : 1);
							}
							else x = 1;
						}
						else x = (B[1][j] == B[0][j-2] ? 0 : 1);/*else only one of the two alternative dips can be selected*/
					}
					//cout << x << '\n';
					x == 0 ? neg(A[q]) : A[q];
			}
		}
		forn(i, 0, p.size()-1){//This is when the dips did not occur alternatively so all such are eligible to be made negative
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
