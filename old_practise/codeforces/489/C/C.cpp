#include         <iostream>
#include         <algorithm>
#include         <functional>
#include         <vector>
#include         <map>
#include         <set>
#include         <string>
#include         <cstring>
#include         <climits>
#include         <cstdlib>
#include         <cmath>
#define pb       push_back
#define eb       emplace_back
#define se       second
#define fi       first
#define all(v)   (v).begin(),(v).end()
#define bug(s,x) fprintf(stderr,"[%s %s : %i]\n",s,#x,x)
#define bg(x)    bug ("here : ", x)
#define inf      (0x7fffffff)
#define eps      ((double)1e-9)
#define scanf    warnscanf_shit = scanf
#define IOS      ios_base::sync_with_stdio(false)
#define PREC     cin.tie (NULL); cout.precision (10); cout << fixed
using namespace std;
int warnscanf_shit;
typedef int64_t ll;
typedef uint64_t ull;
const int mod = 1e9 + 7;
//const int maxn = 1e5 + 10;
//
inline bool ok (int m, int s) {
  return m * 9 >= s;
}

void solve (int m, int s) {
  //check if possible
  int s1, s2;
  s1 = s2 = s;
  if (ok (m, s) == false || (s == 0 && m > 1)) {
	 printf ("-1 -1\n");
  }

  else {
	 char MAX[m + 1], MIN[m + 1];
	 MAX[m] = MIN[m] = '\0';
	 //min

	 for (int i = 0; i < m; ++i) {
		for (int j = (i == 0); j <= 9; ++j) {
		  if (ok (m - i - 1, s1 - j) == true) {
			 MIN[i] = char ('0' + min (s1, j));
			 s1 -= min (s1,j);
			 break;
		  }
		}
	 }

	 //max
	 for (int i = 0; i < m; ++i) {
		for (int j = 9; j >= (i == 0); --j) {
		  if (ok (m - i - 1, s2 - j) == true) {
			 MAX[i] = char ('0' + min (s2, j));
			 s2 -= min (s2,j);
			 break;
		  }
		}
	 }
	 printf ("%s %s\n", MIN, MAX);
  }
}

int main() {
	 //IOS; PREC;
	 int m, s;
	 while ((scanf ("%i%i", &m, &s)) == 2) {
		solve (m, s);
	 }
	 return EXIT_SUCCESS;
}

