/*author* Priyanshu, Rakesh and Vaibhav (from IIT Palakkad) as  ****
 ****  __ _ ___ ___ _   _ _ __ ___   ___   /   \___  __ _  __| |****
 **** / _` / __/ __| | | | '_ ` _ \ / _ \ / /\ / _ \/ _` |/ _` |****
 ****| (_| \__ \__ \ |_| | | | | | |  __// /_//  __/ (_| | (_| |****
 *****\__,_|___/___/\__,_|_| |_| |_|\___/___,' \___|\__,_|\__,_|____
 |_____|   We will get better because we're not dead yet!     |_____|
 ************mr.convict*******iamrakesh28**********vjac*************/
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
int n, scc = 0;
int A[maxn] = {0};
int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
vector <vector <int> > edge;
int vis [51] = {0};

void createG () {
	 for (int i = 0; i < n - 1; ++i)
		  for (int j = i + 1; j < n; ++j)
				if (__gcd (A[i], A[j]) == 1)
					 edge[A[i]].pb (A[j]), edge[A[j]].pb (A[i]);
}
void explore (int x) {
	 vis [x] = 1;
	 for (int j = 0; j < (int) edge[x].size(); ++j) {
		  if (vis[edge[x][j]] == 0)
				explore (edge [x][j]);
	 }
}
int dfs () {
	 int sc = 0;
	 edge.resize(51);
	 for (int i = 0; i < 51; ++i) vis [i] = 0;
	 createG();
	 for (int i = 0; i < n; ++i) {
		  if (vis [A[i]] == 0) {
				++sc;
				explore (A[i]);
		  }
	 }
	 edge.clear();
	 return sc;
}

int main() {
#ifdef CONVICTION
	 if(!freopen ("in", "r", stdin)) return -1;
#endif
	 int t;
	 scanf ("%i", &t);
	 while (t--) {
		  scc = 0;
		  bool prime_use[15] = {0};
		  scanf ("%i", &n);
		  for (int i = 0; i < n; ++i) {
				scanf ("%i", A + i);
		  }
		  int scc = dfs ();

		  if (scc != 1) {
				sort (A, A + n);
				for (int i = 0; i < n; ++i)
					 for (int j = 0; j < 15; ++j)
						  if (A [i] % primes [j] == 0)
								prime_use[j] = 1;

				for (int i = 0; i < 15; ++i)
					 if (prime_use[i] == 0) {
						  A[0] = primes [i];
						  break;
					 }
		  }

		  printf ("%i\n", (scc > 1 ? 1 : 0));
		  for (int i = 0; i < n; ++i) {
				printf ("%i%c", A[i], " \n" [i == n - 1]);
		  }
	 }
	 return 0;
}
