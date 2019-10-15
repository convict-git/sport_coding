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
	//printf("Starts working!\n");//Comment it after debugging
	int n, ai, counter;
	cin >> n;
	vector <int> vec;
	for (int i = 0; i < n; i++){
		cin >> ai;
		if (ai != 0) vec.push_back(ai);
	}
	sort(vec.begin(), vec.end());
	int init = vec.at(0);
	counter = 1;
	for (unsigned int i = 1 ; i < vec.size() ; i++){
		if (vec.at(i)!=init){
			init = vec.at(i);
			counter ++;
		}
	}
	cout << counter << endl;
	return 0;
}