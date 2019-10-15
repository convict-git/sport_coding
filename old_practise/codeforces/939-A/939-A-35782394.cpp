/*
	 ***************************************************************
	 ||   Author                         {Priyanshu Shrivastav}	  || 
	 ||   handle																	 {mr.convict}	  || 
	 ||   github																  {convict-git}	  || 
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
	int n, ai, temp;
	cin >> n;
	if (n == 2){
		cout << "NO" << endl;
		return 0;
	}
	vector <pair<int,int> >vec(n);
	for (int i = 0; i < n; i++){
		cin >> ai;
		vec[i].first = i+1;
		vec[i].second = ai;
	}

	for (int i = 0; i < n; i++){
		temp = vec[vec[i].second - 1].second;
		if (vec[temp - 1].second == vec[i].first){
			cout << "YES" << endl;
			return 0;
		}
	}
	cout << "NO" << endl; 
return 0;
}