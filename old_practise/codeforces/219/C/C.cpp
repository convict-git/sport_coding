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

int n, k, sz, ans = 0, comp = 0, color = 0;
vector <char> s;
int col [26] = {0};
void solve() {
	char prv = 'm', cur = 'm', nxt;
	sz = (int) s.size();

	for (auto c : s) {
		if (col[(int) (c - 'A')] == 0) ++color;
		col[(int) (c - 'A')] = 1;
	}

	while (color < k) {
		if (col[comp] == 0) {
			++color;
		}
		col[comp] = 1;
		++comp;
		comp %= 26;
	}
	assert (color == k);
	if (k == 2) {
		char ch[2] = {'x', 'y'};
		for (int i = 0; i < 26; ++i) {
			if (col[i] == 1 && ch[0] == 'x') ch[0] = (char) ('A' + i);
			else if (col[i] == 1) {
				ch[1] = (char) ('A' + i);
				break;
			}
		}
		int diff[2] = {0, 0};
		for (int i = 0; i < sz; ++i) {
			for (int j = 0; j < 2; ++j) {
				if (i%2) diff[j] += ch[j] != s[i];
				else diff[j] += ch[(j + 1)%2] != s[i];
			}
		}
		auto print = [=] (int x)->void {
			printf ("%i\n", diff[(x + 1)%2]);
			for (int i = 0; i < sz; ++i) {
				printf ("%c", ch[(i + x)%2]);
			} printf ("\n");
		};
		if (diff[0] < diff[1]) print (1);
		else print (0);

	}
	else {
		bool ok = false;
		auto solver = [&] ()->void {
			for (int i = 1; i < sz; ++i) {
				if (s[i] == s[i - 1]) {
					ok = false;
					i < sz - 1 ? nxt = s[i + 1] : nxt = s[i];
					cur = s[i];
					prv = s[i - 1];
					int findIdx = 0;
					char match;
					while (findIdx < 26) {
						match = (char) (findIdx + 'A');
						if (col[findIdx] == 1 && match != cur && match != prv && match != nxt) {
							ok = true;
							break;
						}
						++findIdx;
					}
					if (ok) {
						s[i] = match;
						ans += 1;
						continue;
					}
					else break;
				}
			}
		};

		solver();
		printf ("%i\n", ans);
		for_each (all (s), [] (const char &c) { printf ("%c", c); });
		printf ("\n");
	}
}

int main() {
	//IOS; PREC;
	char ch;
	scanf ("%i%i", &n, &k); getchar();
	for (int i = 0; i < n; ++i) {
		ch = getchar();
		if (ch - 'A' >= 0 && 'Z' - ch >= 0) s.push_back (ch);
	}
	assert ((int)s.size() == n);
	solve();
	return EXIT_SUCCESS;
}

