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

int main(){
	int n, d, ai, maxi, diff;
	cin >> n >> d;
	if (n == 0) return 1;
	if (n == 1){ cout << 0 << endl; return 0; }

	vector <int> vec1;
	vector <int> vec2;
	set <int> sec1;
	for (int i = 0 ; i < n ; i++){
		cin >> ai;
		vec1.push_back(ai);
		sec1.insert(ai);
	}

	if (d == 0 && sec1.size() == 1){
		cout << 0 << endl; return 0; }
	else if ( d == 0 && sec1.size() == n){
		cout << n-1 << endl; return 0;}

	sort(vec1.begin(), vec1.end());
	maxi = 0;
	for (int i = 0; i < n - 1; i++)
		for (int j = i+1; j < n; j++){
			diff = vec1.at(j) - vec1.at(i);
			if (diff > maxi && diff <= d){
				maxi = diff;
			}
		}
	for (int i = 0; i < n - 1; i++)
		for (int j = i+1; j < n; j++){
			diff = vec1.at(j) - vec1.at(i);
			if (diff == maxi && diff <= d)
				vec2.push_back(i - j + vec1.size() -1);
		}
	if(vec2.size()!=0){
		sort(vec2.begin(), vec2.end());
		cout << vec2.at(0) << endl;}
	else
		cout << n - 1 << endl;
	return 0;
	cout << endl;
}