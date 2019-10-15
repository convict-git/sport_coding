#include<bits/stdc++.h>
using namespace std;
#define forn(i, n)             for(int i = 0; i < n; i ++)
#define forn1(i, n)            for(int i = 1; i <= n; i ++)
#define pb push_back
#define ll long long int
#define fi first
#define se second
#define ii  pair<long long int, long long int>
#define vi  vector <long long int>
#define vii vector <pair <long long int, long long int > >
#define all(cont)  cont.begin(), cont.end()
#define EPS 1e-9
#define MOD 1000000007
#define range 60
#define IOS ios::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#pragma GCC optimize ("Ofast")


char mat[range][range];

bool chk1(int i,int j){
	if(mat[i][j] == '1' && mat[i+1][j] == '1' && mat[i+1][j+1] == '1' && mat[i][j+1] == '1')return true;
	return false;
}

bool chkcom(int i,int j){
	if(mat[i][j] == '1' && mat[i+1][j] == '1' && mat[i+1][j+1] == '1' && mat[i][j+1] == '1')return true;
	if(mat[i][j] == '1' && mat[i+1][j] == '1' && mat[i+1][j-1] == '1' && mat[i][j-1] == '1')return true;
	if(mat[i][j] == '1' && mat[i-1][j] == '1' && mat[i-1][j+1] == '1' && mat[i][j+1] == '1')return true;
	if(mat[i][j] == '1' && mat[i-1][j] == '1' && mat[i-1][j-1] == '1' && mat[i][j-1] == '1')return true;
	return false;
}

int main(){

//    freopen("input.txt","r",stdin);
    IOS;
    clock_t clk = clock();
	int n,m;cin>>n>>m;
	forn1(i,n){
		forn1(j,m)cin>>mat[i][j];
	}

	bool pos = true;
	forn1(i,n){
		forn1(j,m){
			if(mat[i][j] == '1'){
				pos = chkcom(i,j);
			}
		}
	}

	if(pos == false){
		cout<<-1<<endl;
		return 0;
	}
	vii ans;
	forn1(i,n-1){
		forn1(j,m-1){
			if(mat[i][j] == '1'){
				if(chk1(i,j))ans.pb({i,j});
			}
		}
	}
	cout<<ans.size()<<endl;
	forn(i,ans.size())cout<<ans[i].fi<<" "<<ans[i].se<<endl;
    cerr << endl << setprecision(10) << fixed << (double)(clock() - clk) / CLOCKS_PER_SEC;
    return 0;
}
