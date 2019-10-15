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
	int n, ai;
	cin >> n;
	vector <pair <int, string> > v={{0, "chest"}, {0, "biceps"}, {0, "back"}};
	for (int i = 0; i < n; i++){
		cin >> ai;
		v.at(i%3) = make_pair(v[i%3].first+ai,v[i%3].second);
	}
	sort(v.rbegin(), v.rend()); cout << v[0].second << endl;
	return 0;
}