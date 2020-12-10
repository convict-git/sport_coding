#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
/******************************************
* AUTHOR : PANDRAVISAM SHIVA SANTHOSH *
* Handle : santhosh_80 *
* INSTITUTION : IIT Palakkad *
******************************************/
#define ll long long int
#define pii pair<int,int>
#define pll pair<long long, long long>
#define vi vector<int>
#define vll vector<long long >
#define umap unordered_map
#define all(v) (v).begin(),(v).end()
#define pb push_back
#define eb emplace_back
#define f first
#define s second
#define inf LLONG_MAX
#define neg_inf LLONG_MIN
#define next_line cout << "\n"
#define what_is(x) cerr << #x << " is " << x << "\n";
#define rep(i,a,b) for(int i = a; i < b; i++)
#define repj(j,a,b) for(int j = a; j < b; j++)

inline void read0(auto &v, int n) {
	for(int i = 0; i < n; i++){cin >> v[i];}
}
inline void read1(auto &v, int n) {
	for(int i = 1; i <= n; i++){cin >> v[i];}
}
inline void out0(auto &v, int n) {
	for(int i = 0; i < n; i++){cout << v[i] << " ";}
}
inline void out1(auto &v, int n){
	for(int i = 1; i <= n; i++){cout << v[i] << " ";}
}
inline void auto_print(auto &v){
	for(auto x: v)cout << x << " ";
}

const ll mod = 1000000007;
const ll N = 1e6;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t; cin >> t;
	while(t--){
		int n,q; cin >> n >> q;
		string s;
		cin >> s;
		int count1 = 0, count2 = 0;
		vector<int> dp1(n,0);
		vector<int> dp2(n,0);

		for(int i = 0; i < n; i++){
			if(s[i] == '0')dp1[i]=1;
			else dp2[i] = 1;;
		}

		while(q--){

			int l,r; cin >> l >> r;
			l--,r--;

			bool flag = false;

			for(int i = 0; i < l; i++){
				if(s[l] == '0'){
					if(dp1[i] == 1){
						flag = true;
					}
				}
				else{
					if(dp2[i] == 1){
						flag = true;
					}
				}
			}

			for(int i = r+1; i < n; i++){

				if(s[r] == '0'){
					if(dp1[i] == 1){
						flag = true;
					}
				}
				else{
					if(dp2[i] == 1){
						flag = true;
					}
				}
			}

			if(l == r){
				cout << "NO\n";
			}
			else if(flag){
				cout << "YES\n";
			}
			else{
				cout << "NO\n";
			}

		}

	}
 	return 0;
}
