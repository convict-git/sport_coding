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
ull powOften[18];
void init () {
	powOften[0] = 1;
	for (int i = 1; i < 18; ++i)
		powOften[i] = 10*powOften[i - 1];
}

inline int findit (string x) {
	return (int) (x[0] - '0') - (x[0] > x[x.size() - 1]);
}

ull findPermutations (string x) {
	cerr << x << '\n';
	int m = findit (x);
	cerr << "m " << m << '\n';
	int sz = (int) x.size();
	ull sm = 0;
	if (x.size() == 1 && x[0] == '1') return 0*1ull;
	for (int k = 1; k < sz; ++k) {
		sm +=  9 * powOften[max (0, k - 2)];
	}
	cerr << "Sum now " << sm << '\n';
	ull tmp = 0;
	for (int i = 1; i < sz - 1; ++i) {
		tmp = tmp * 10 + (x[i] - '0');
	}
	cerr << "tmp " << tmp << '\n';
	if ((int) (x[0] - '0') == m) {
		sm += tmp;
		sm += max (0, m - 1) * powOften[max (0, sz - 2)];
		if (tmp == 0) sm += 1;
	}
	else {
		sm += max (0, m) * powOften[max (0, sz - 2)];
		if (tmp) {
			tmp-=1;
			sm += tmp;
		}
	}
	cerr << "Sum now " << sm << '\n';
	return sm;
}

string l, r;
int m, n;
int main() {
	IOS; PREC;

	init();
	cin >> l >> r;
	ull lower = findPermutations (l);
	if (lower != 0 && l[0] == l[l.size() - 1]) --lower;
	ull upper = findPermutations (r);
	//cerr << "upper " << upper << ' ' << "lower " << lower << '\n';
	cout << upper - lower << '\n';
	return EXIT_SUCCESS;
}

