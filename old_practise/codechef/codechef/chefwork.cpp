/*author* Priyanshu Shrivastav
*from*(IIT Palakkad)
 *_ __ ___  _ ______ ___  _ ____   ___  ___| |_
 | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __|
 | | | | | | | | (_| (_) | | | \ V /| | (__| |_
 |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__|
 wHEN i WROTE THIS, ONLY gOD AND i UNDERSTOOD WHAT i WAS DOING
 * nOW, ONLY gOD KNOWS*/

#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define se second
#define fi first
#define pii pair <int, int>
#define vi vector <int>
#define forn(i, j, k) for (int i = j; i < (int)k; i++)
#define forN(i, j, k) for (int i = k-1; i >= j; i--)
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define mod(x) ((x)%N)

typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int ui;

using namespace std;

const ui N = 1000000007;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.precision(10); cout << fixed;

#ifdef CONVICTION
	if(!freopen("in", "r", stdin)) return -1;
#endif

	int n, *c, *t, m1, m2, m3;
	m1 = m2 = m3 = INT_MAX;
	cin >> n;
	c = new int [n];
	t = new int [n];
	forn(i, 0, n) cin >> c[i];
	forn(i, 0, n) cin >> t[i];
	forn(i, 0, n){
		switch (t[i]){
			case (1):
				c[i] < m1 ? m1 = c[i] : m1;
				break;
			case (2):
				c[i] < m2 ? m2 = c[i] : m2;
				break;
			case (3):
				c[i] < m3 ? m3 = c[i] : m3;
		}
	}
	if (m2 == INT_MAX || m1 == INT_MAX)
		cout << m3 << '\n';
	else if (m3 == INT_MAX)
		cout << m1+m2 << '\n';
	else
		m1+m2 < m3 ? cout << m1+m2 << '\n' : cout << m3 << '\n';

//Beware no shit stuff here!
	return 0;
}

