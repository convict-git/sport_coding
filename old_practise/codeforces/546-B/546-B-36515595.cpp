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
	int n, counter = 0, counter1;
	cin >> n;
	vector <int> v(n);
	set <int> s; set <int>::iterator it;
	for (int i = 0; i < n; i++){
		cin >> v.at(i);
		s.insert(v.at(i));
	}
	sort(v.begin(), v.end());

	for (int i = 0 ; i < n-1; i++){
		if (v.at(i+1) == v.at(i)){
			counter1 = 0;
			do{
				counter1+=1;
				it = s.find(v.at(i+1)+counter1); 
			}while(it!=s.end());
			counter+=counter1;
			s.insert(v.at(i+1)+counter1);
		}
	}
	cout << counter << endl;
	return 0;
}