#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
	int n, coin = 0, last = -1;
	cin >> n;
	char c;
	pair <int, int> p;
	int S[n];
	p.first = 0;
	p.second = 0;

	for (int i = 0; i < n; i++){
		cin >> c;
		if (c == 'U') S[i] = 1;
		else if (c == 'R') S[i] = 0;
	}
	for (int i = 0; i < n-1; i++){
		if (S[i] == 1){p.second ++; last = 1;}
		else if (S[i] == 0){p.first ++; last = 0;}

		if (p.first == p.second){
			if (last == 1){
				if (S[i+1] == 1)
					coin++;
			}
			else if (last == 0){
				if (S[i+1] == 0)
					coin++;
			}
		}
	}
	cout << coin << endl;

}