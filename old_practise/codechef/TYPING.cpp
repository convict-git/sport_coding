/*author* Priyanshu Shrivastav and Rakesh Kumar(from IIT Palakkad) *
 ****  __ _ ___ ___ _   _ _ __ ___   ___   /   \___  __ _  __| |****
 **** / _` / __/ __| | | | '_ ` _ \ / _ \ / /\ / _ \/ _` |/ _` |****
 ****| (_| \__ \__ \ |_| | | | | | |  __// /_//  __/ (_| | (_| |****
 *****\__,_|___/___/\__,_|_| |_| |_|\___/___,' \___|\__,_|\__,_|____
 |_____|                                                      |_____|
 *******************************************************************/

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <set>
#include <string>
#include <climits>
using namespace std;

#define pb       push_back
#define eb       emplace_back
#define se       second
#define fi       first
#define all(v)   (v).begin(),(v).end()
#define sqr(x)   ((x)*(x))
#define Mod(x)   ((x)%_mod)
#define bug(s,x) fprintf(stderr,"%s %s : %i\n",s,#x,x)
#define inf      (0x7fffffff)
#define eps      ((double)1e-9)
#define scanf    warnscanf_shit = scanf
int warnscanf_shit;


typedef int64_t ll;
typedef uint64_t ull;

const int maxn = (int)2e6 + 10;
const int _mod = (int)1e9 + 7;

int n;
set <string> s;
inline int mp (char c) { return ((c == 'j' || c == 'k') ? 1 : 0); }

int main() {
#ifdef CONVICTION
	 if(!freopen ("in", "r", stdin)) return -1;
#endif
	 ios_base::sync_with_stdio (false);
	 cin.tie (NULL); cout.precision (10); cout << fixed;
	 /*solution starts here...*/
	 int t;
	 cin >> t;
	 while (t--) {
		  int gtme = 0, cur = 0, ctme;
		  string str;
		  cin >> n;
		  for (int i = 0; i < n; ++i) {
				ctme = 0;
				int j = 0;
				cin >> str;
				cur = mp (str[0]) ? 0 : 1;

				while (j < (int) str.size()) {
					 ctme += (mp (str[j]) != cur ? 2 : 4);
					 cur = mp (str[j]);
					 ++j;
				}
				if (s.find (str) != s.end()) {
					 ctme>>=1;
				}
				s.insert (str);
				gtme += ctme;
		  }
		  cout << gtme << '\n';
		  s.clear();
	 }
	 return 0;
}
