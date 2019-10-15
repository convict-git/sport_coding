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
	int n, ai, flag = 0;
	cin >> n;
	vector < vector<int> > v;
	set <int> s; vector <int> v1;

	for (int j = 0; j < n; j++){ vector <int> temp;
		for (int i = 0 ; i < 6; i++){ cin >> ai; temp.push_back(ai); }
		temp.push_back(0); v.push_back(temp);temp.clear(); }

	for (int p = 1; p <=n; p++) for (int i = 0; i < 7; i++) for (int j = 0; j < 6;j++){
					s.insert(10*(v[p%n].at(i)) + (v[(p+1)%n].at(j)));
					s.insert(10*(v[n-1-(p%n)].at(i)) + (v[n-1-((p+1)%n)].at(j)));
		}
	s.erase(0);
	copy(s.begin(), s.end(), back_inserter(v1));

	vector <int>::iterator it = v1.begin();
	for (unsigned int i = 1; i < v1.size() && it!= v1.end(); i++){
		if (*it != i){cout << i-1 << endl; return 0;}it++;
	}
	cout << v1.at(v1.size()-1) << endl;
	int stop_s=clock();
	//cout << "time taken: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << endl;
	return 0;
}