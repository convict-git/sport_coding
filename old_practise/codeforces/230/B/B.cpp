#include         <bits/stdc++.h>
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
const int maxn = 1e6 + 10;
bool SV[maxn];
int n;
ll x;

void sieve () {
  int N = maxn;
  for (int i = 0; i < N; ++i) SV[i] = false;
  for (int i = 2; i < sqrt (N); ++i) {
	 int k = 0;
	 while (i * (i + k) < N) {
		SV[i * (i + k)] = true;
		++k;
	 }
  }
  SV[1] = true;
  SV[0] = true;
}
inline bool isSqr (ll s) {
  ll sq = (ll) sqrtl (s);
  return sq*sq == s;
}

void solve () {
  cin >> x;
  if (isSqr (x)) {
	 ll sq = (ll) sqrtl (x);
	 if (!SV[sq]) cout << "YES\n";
	 else cout << "NO\n";
  }
  else cout << "NO\n";
}

int main() {
	 //IOS; PREC;
  sieve ();
  cin >> n;
  while (n--) solve ();
  return EXIT_SUCCESS;
}

