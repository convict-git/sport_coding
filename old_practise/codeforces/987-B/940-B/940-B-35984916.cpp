/*
 *  ***************************************************************
 *   ||   Author                         {Priyanshu Shrivastav}	  || 
 *    ||   email  {official[dot]mr[dot]convict[at]gmail[dot]com}   || 
 *     ***************************************************************
 *      **_ __ ___    _ __    ___    ___    _ __   __   __ (_)   ___  | |_ 
 *       | '_ ` _ \  | '__|  / __|  / _ \  | '_ \  \ \ / / | |  / __| | __|
 *        | | | | | | | |    | (__  | (_) | | | | |  \ V /  | | | (__  | |_ 
 *         |_| |_| |_| |_|     \___|  \___/  |_| |_|   \_/   |_|  \___|  \__|
 *          ***************************************************************
 *           */

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
	int start_s=clock();
	unsigned long long int n, k, A, B, cost = 0, flag = 0;
	cin >> n >> k >> A >> B;
	while (n != 1){
		if (n%k==0 && n >= k && k!=1 && flag != 1){
			if(B <= (n - (n/k))*A){ cost+=B; n/=k;
			}
			else {
				if (n==k){ cost+=((n-1)*A); n-=(n-1); }
				else{ cost+=(k*A); n-=k; }
				flag = 1;
			}
		}
		else if (flag == 1){ cost+=(n-1)*A; n-=(n-1); }
		else if (n <= k || k==1){ cost+=((n-1)*A); n-=(n-1); } 
		else { cost+=(n%k)*A; n-=n%k;}
		//cout << n << endl;
	}
	cout << cost << endl;
	int stop_s=clock();

	//cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	return 0;
}