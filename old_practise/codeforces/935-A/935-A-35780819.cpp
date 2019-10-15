#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]){
	int n, counter = 0;
	cin >> n;

	for (int i = 2; i <= n; i++){
		if (n%i == 0)
			counter++;
	}
	cout << counter << endl;

	return 0;
}