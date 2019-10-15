/*author* Priyanshu Shrivastav
 *_ __ ___  _ __ ___ ___  _ ____   ___  ___| |_ 
 | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __|
 | | | | | | | | (_| (_) | | | \ V /| | (__| |_ 
 |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__|
 When I wrote this, only God and I understood what I was doing
    * Now, God only knows*/

#include <bits/stdc++.h>
#define fo(n) for(int i=0;i<n;i++)
#define e(x) cout<<x<<" "
using namespace std;

int main(int argc, char *argv[]){
	int n, m, p=0;
	cin>>n >> m; int a[n];
	fo(n) cin >> a[i]; sort(a,a+n); fo(m) a[i] < 0 ? p+=(-1*a[i]) : p;
	e(p)<<endl;
}