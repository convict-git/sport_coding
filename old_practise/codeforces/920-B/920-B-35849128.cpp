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

void printVec(vector <int>* vec){
	for (vector <int>::iterator it = vec->begin(); it!=vec->end(); it++)
		cout << *it << " ";
	cout << endl;
}

void logic(vector < pair<int,int> > v){
	vector <int> v1;
	v1.push_back(v[0].first);
	for (unsigned int k = 1; k < v.size(); k++){
		if (v[k].second < v[k-1].first+1){
			v.erase(v.begin()+k);
			k--;
			v1.push_back(0);
		}
		else{
			if (v[k-1].first + 1 < v[k].first)
				v1.push_back(v[k].first);
			else{
				v1.push_back(v[k-1].first+1);
				v[k].first = v[k-1].first+1;
			}
		}
	}
	printVec(&v1);
}

int main(int argc, char *argv[]){
	int t, n, l, r;
	cin >> t;
	for (int i = 0; i < t; i++){
		cin >> n;
		vector < pair<int,int> > v;
		for (int j = 0; j < n; j++){
			cin >> l >> r;
			v.push_back(make_pair(l,r));
		}
		logic(v);
	}
	return 0;
}