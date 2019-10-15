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
  IOS; PREC;
	 int Ar[3];
	 for (int i = 0; i < 3; ++i)
		cin >> Ar[i];
	 sort (Ar, Ar + 3);
	 ll sm = Ar[0] + 1ll*Ar[1] + 1ll*Ar[2];
	 ll tw = sm - 1ll*Ar[2];
	 sm/=3;
	 cout << min (sm, tw) << '\n';

	 return EXIT_SUCCESS;
}

