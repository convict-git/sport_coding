/*
	 ***************************************************************
	 ||   Author                         {Priyanshu Shrivastav}	  || 
	 ||   email  {official[dot]mr[dot]convict[at]gmail[dot]com}   || 
	 ***************************************************************
	**_ __ ___    _ __    ___    ___    _ __   __   __ (_)   ___  | |_ 
	 | '_ ` _ \  | '__|  / __|  / _ \  | '_ \  \ \ / / | |  / __| | __|
	 | | | | | | | |    | (__  | (_) | | | | |  \ V /  | | | (__  | |_ 
	 |_| |_| |_| |_|     \___|  \___/  |_| |_|   \_/   |_|  \___|  \__|
	 ***************************************************************
	 */

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
	int n, p = 1, q = 2, m = p+q, i = 2;
	cin >> n;
	if (n == 1)cout << 'O' << endl;
	else{
		cout << 'O' << 'O';
	while (i <= n-1){
		if(i == m-1){ cout << 'O'; p = q; q = m; m = p+q;
		}
		else cout << 'o';
		i++; }
	}


	return 0;
}