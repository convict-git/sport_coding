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
	int start_s=clock();
	int n, pos, l, r, counter=0;
	cin >> n >> pos >> l >> r;

	if (n-r > 0 || l > 1){
		if (n-r>0 && l>1){
			abs(pos-l) >= abs(pos-r) ? counter+=abs(pos-r) : counter+=abs(pos-l);
			counter+=r-l+2;
		}
		else if (n-r>0) counter+=abs(pos-r)+1;
		else if (l>1) counter+=abs(pos-l)+1;
	}
	cout << counter << endl;

	int stop_s=clock();
	//cout << "time taken: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	return 0;
}
