#include         <iostream>
#include         <algorithm>
#include         <cstdlib>
#include         <cmath>
#include         <vector>
#include         <set>
#include         <string>
#include         <climits>
#include         <map>
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
#define PREC     cin.tie (NULL); cout.precision (10); cout << fixed;
using namespace std;
int warnscanf_shit;

typedef int64_t ll;
typedef uint64_t ull;
const int maxn = 1e5 + 10;
const int mod_ = 1e9 + 7;
ll sz, p;
set <ll> s;
pair <ll, ll> solve () {
	 set <ll> :: iterator it = s.lower_bound (p);
	 ll k = (ll)sqrt (*it);
	 if (p == *it) {
		  return {sz/2 + (k - 1)/2 + 1, sz/2 + (k - 1)/2 + 1};
	 } else {
		  ll i0, j0, ld, lr;
		  ll diff = *it - p;
		  --k;
		  j0 = i0 = sz/2 + k/2;
		  ld = diff/k, lr = diff%k;
		  switch (ld)
		  {
			 	case 0 : i0 -= lr; break;
				case 1 : i0 -= k, j0 -= lr; break;
				case 2 : i0 -= (k - lr), j0 -= k; break;
				case 3 : j0 -= k - lr; break;
		  }
		  return  {i0 + 1, j0 + 1};
	 }
}

int main() { //IOS; PREC;
	 for (int i = 0, k = 1; i <= 100000; ++i, k+=2)
		  s.insert (1ll *k * k);

	 while (scanf ("%ld%ld", &sz, &p), (sz || p)) {
		  pair <ll, ll> sl = solve ();
		  printf ("Line = %ld, column = %ld.\n", sl.fi, sl.se);
	 }
	 return 0;
}
