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
	int n, v1=0, v2=0, ai, maxi=0;
	char c;
	cin >> n; assert(n <= 1e6);
	set <int> s;
	for (int i = 0; i < n; i++){
		cin >> c >> ai;
		if (c == '+'){ s.insert(ai);
			if (v2 > 0) {v2--; v1++;}
			else v1++;  
		} else if (c == '-'){
			if (s.find(ai)!=s.end()){ v2++; v1--;}
			else v2++;
		} maxi = max(maxi, v2+v1);
	}
	cout << maxi << endl;
	return 0;
}