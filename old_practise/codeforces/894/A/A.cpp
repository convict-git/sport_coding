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

typedef int64_t ll;
typedef uint64_t ull;

const int maxn = (int)2e6 + 10;
const int _mod = (int)1e9 + 7;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie (NULL); cout.precision (10); cout << fixed;
  /*solution starts here...*/
  string s;
  cin >> s;
  int cnt, st, scur[s.size()];
  st = cnt = 0;
  for (int i = 0; i < (int)s.size(); ++i) {
		if (s[i] == 'Q') ++st;
		if (s[i] == 'A') scur[i] = st;
  }
  for (int i = 0; i < (int)s.size(); ++i) {
		if (s[i] == 'A') cnt += scur[i] * (st - scur[i]);
  }
  cout << cnt << '\n';
  return 0;
}

