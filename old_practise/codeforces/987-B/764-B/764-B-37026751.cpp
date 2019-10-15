/*author* Priyanshu Shrivastav
 *_ __ ___  _ __ ___ ___  _ ____   ___  ___| |_ 
 | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __|
 | | | | | | | | (_| (_) | | | \ V /| | (__| |_ 
 |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__|
 When I wrote this, only God and I understood what I was doing
 * Now, only God knows*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define se second
#define fi first
#define fr(x,y,z) for(auto x=y;x!=z;++x)
#define fo(n) for(auto i=0;i<n;i++)
#define fm(m,n) fr(i,0,m) fr(j,0,n)
#define all(v) v.begin(),v.end()
#define vit vector<int>::iterator it
#define sit set<int>::iterator it
#define R(x,y); {er(x,y); return 0;}

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;
int n;

int main(int argc, char *argv[]){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin >> n; 
	int A[n];
	fo(n) cin >> A[i];
	fo(n/2) if(i%2 == 0) swap(A[i], A[n-i-1]);
	fo(n) cout << A[i] << " "; cout << "\n";

//Beware no shit stuff here!
}