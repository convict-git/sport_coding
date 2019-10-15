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
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7;
int N;
vector <pair <int, int> > vp;

int main() {
	 scanf ("%i", &N);
	 vp.resize(N);
	 for (int i = 0; i < N; ++i) {
		scanf ("%i%i", &vp[i].fi, &vp[i].se);
	 }
	 sort (all (vp));
	 int cur = min (vp[0].fi, vp[0].se);
	 for (int i = 1; i < N; ++i) {
		int tmp = min (vp[i].fi, vp[i].se);
		if (tmp >= cur) cur = tmp;
		else cur = max (vp[i].fi, vp[i].se);
	 }
	 printf ("%i\n", cur);

	 return EXIT_SUCCESS;
}

