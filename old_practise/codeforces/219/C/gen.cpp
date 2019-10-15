#pragma GCC      optimize ("Ofast")
#include         <iostream>
#include         <iomanip>
#include         <functional>
#include         <algorithm>
#include         <vector>
#include         <map>
#include         <set>
#include         <string>
#include         <cstring>
#include         <climits>
#include         <cstdlib>
#include         <cmath>
#include         <iomanip>
#include         <cassert>
#define pb       push_back
#define eb       emplace_back
#define se       second
#define fi       first
#define all(v)   (v).begin(),(v).end()
#define bug(s,x) fprintf(stderr,"[%s %s : %i]\n",s,#x,x),fflush(stderr)
#define bg(x)    bug ("bug : ", x)
#define inf      (0x7fffffff)
#define eps      ((double)1e-9)
#define scanf    warnscanf_shit = scanf
#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed

using namespace std;
int warnscanf_shit;
typedef long long ll;
typedef unsigned long long ull;
const int MOD = 1e9 + 7;
//const int MAXN = 1e5 + 10;

int main() {
	//IOS; PREC;

	srand(time(0));
	int n = 5e5 + 10;
	vector <char> vi;
	set <char> s;
	printf ("%i ", n);
	while (n--) {
		int cn = rand()%26;
		while (cn < 0) cn = rand()%26;
		vi.push_back ((char) ('A' + cn));
		s.insert ((char) ('A' + cn));
	}
	printf ("%i\n", (int)s.size());
	for_each (all (vi), [] (const char &c) { printf ("%c", c); });
	printf ("\n");

	return EXIT_SUCCESS;
}


