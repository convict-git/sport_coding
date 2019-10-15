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
	int t, n, k, ai, mini, maxi, bi;
	cin >> t;
	for (int i = 0; i < t; i++){
		mini = 0; maxi = 0;
		cin >> n >> k;
		for (int j = 0; j < k; j++){
			cin >> ai;
			bi = ai - mini - 1 == 1 ? 1 : ceil((ai - mini - 1)/2.0);
			if (j == 0) maxi = ai - mini - 1;
			if(j == k - 1){
				maxi = max(bi,maxi);
				maxi = max(n - ai, maxi);
			}
			else maxi = max(bi,maxi);
			mini = ai;
		}
		cout << maxi + 1<< endl;
	}
}