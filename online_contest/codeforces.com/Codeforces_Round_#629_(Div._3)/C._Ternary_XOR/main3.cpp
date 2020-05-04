#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;
/******************************************
* AUTHOR : PANDRAVISAM SHIVA SANTHOSH *
* Handle : santhosh_80 *
* INSTITUTION : IIT Palakkad *
******************************************/
typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> indexed_set;
#define ll long long int
#define mod 1000000007
#define rep(i,a,b) for(int i=a;i<b;i++)
#define pii pair<int,int>
#define all(v) (v).begin(),(v).end()
#define S(x) scanf("%d",&(x))
#define P(x) printf("%d\n",(x))
#define Sl(x) scanf("%lld",&(x))
#define Pl(x) printf("%lld\n",(x))
#define pb push_back
#define f first
#define s second


int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int t; cin >> t ;
	while(t--) {
		int n ; cin >> n ;
		string str  ;cin >> str ;
		vector<char> str1,str2 ;
		int flag = 0 ;
		for(int i = 0; i < n ; i++) {

				if(!flag) {
						if(str[i] == '2') {
							str1.pb('1');str2.pb('1') ;
						}
						else if (str[i] == '1') {
							str1.pb('0');str2.pb('1') ;
							flag = 1 ;
						}
						else{
							str1.pb('0');str2.pb('0') ;
						}
				}
				else{
					if(str[i] == '2'){
						str1.pb('2') ; str2.pb('0') ;
					}
					else if(str[i] == '1'){
						str1.pb('1') ; str2.pb('0') ;
					}
					else{
						str1.pb('0');str2.pb('0') ;
					}
				}
		}
		for(auto x :str2)cout << x ;
		cout << "\n" ;
		for(auto x : str1)cout << x ;
		cout << "\n" ;
	}
 	return 0;
}
