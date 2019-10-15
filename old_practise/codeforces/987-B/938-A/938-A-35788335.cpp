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

void logic(vector <char>* vec, int *hi){
	*hi = 0;
	int k = 1;
	char temp1, temp2;
	set <char> S{'a','e','i','o','u','y'};
	for (unsigned int i = k; i < vec->size(); i++){
		temp1 = vec->at(i);
		temp2 = vec->at(i-1);
		set <char>::iterator it = S.find(temp1);
		if (it!=S.end()){
			set <char>::iterator IT = S.find(temp2);
			if (IT!=S.end()){
				vec->erase(vec->begin()+i);
				*hi = 1;
				k = i;
			}
		}
	}
}

int main(){
	int n, flag;
	char c;
	cin >> n;
	vector <char> v;
	for (int i = 0; i < n; i++){
		cin >> c;
		v.push_back(c);
	}
	flag = 1;
	while(flag == 1){
		logic(&v, &flag);
	}
	for (unsigned i = 0; i < v.size(); i++)
		cout << v.at(i);
	cout << endl;
	return 0;
}