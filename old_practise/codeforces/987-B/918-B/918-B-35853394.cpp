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
	int n, m;
	string name, ip, command, temp;
	vector < pair<string,string> > v;
	cin >> n >> m;
	for (int i = 0; i < n; i++){
		cin >> name >> ip;
		v.push_back(make_pair(name,ip));
	}
	for (int i = 0; i < m; i++){
		cin >> command >> ip;
		ip.erase(ip.end()-1);
		for (int j = 0; j < n; j++)
			if (ip.compare(v[j].second) == 0){
				ip.append(";",1);
				temp = v[j].first;
				temp.insert(0, "#", 1);
				cout << command << " " << ip << " " << temp << endl;
			}
	}return 0;
}