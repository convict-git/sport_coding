#include <iostream>
#include <algorithm>
#include <vector>
#include <climits>
#pragma GCC optimize ("Ofast")

using namespace std;

#define pb push_back
#define eb emplace_back
#define se second
#define fi first
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define Sqr(x) ((x)*(x))
#define Mod(x) ((x)%_mod)
#define inf (0x7fffffff)
#define eps ((double)1e-9)

typedef long long ll;

const int maxn = (int)2e6 + 10;
const int _mod = (int)1e9 + 7;

ll sTree [maxn];
ll lazy [maxn] = {0};
int A [maxn];
char buffer [100];

inline int mid (int ss, int se) {return ss + ((se - ss)>>1);}

void create (int ss, int se, int si)
{
	 if (ss == se)
	 {
		  sTree [si] = A [ss], lazy [si] = 0;
		  return;
	 }
	 create (ss, mid (ss, se), (si << 1) + 1);
	 create (mid (ss, se) + 1, se, (si << 1) + 2);
	 sTree [si] = min (sTree [(si << 1) + 1], sTree [(si << 1) + 2]);
	 lazy [si] = 0;
}
void updLazy (int ss, int se, int si)
{
		  sTree [si] += lazy [si];
		  if (ss != se)
				lazy [(si << 1) + 1] += lazy [si], lazy [(si << 1) + 2] += lazy [si];
		  lazy [si] = 0;
}
ll get (int ss, int se, int qs, int qe, int si)
{
	 if (lazy [si] != 0) updLazy (ss, se, si);
	 if (ss > qe || se < qs) return LLONG_MAX;
	 if (ss >= qs && se <= qe) return sTree [si];

	 ll lgets = get (ss, mid (ss, se), qs, qe, (si << 1) + 1);
	 ll rgets = get (mid (ss, se) + 1, se, qs, qe, (si << 1) + 2);
	 return (lgets < rgets ? lgets : rgets);
}
void update (int ss, int se, int qs, int qe, int diff, int si)
{
	 if (lazy [si] != 0) updLazy (ss, se, si);
	 if (ss > qe || se < qs) return;
	 if (ss >= qs && se <= qe)
	 {
		  sTree [si] += diff;
		  if (ss != se)
		  {
				lazy [(si << 1) + 1] += diff;
				lazy [(si << 1) + 2] += diff;
		  }
		  return;
	 }
	 update (ss, mid (ss, se), qs, qe, diff, (si << 1) + 1);
	 update (mid (ss, se) + 1, se, qs, qe, diff, (si << 1) + 2);
	 sTree [si] = min (sTree [(si << 1) + 1], sTree [(si << 1) + 2]);
}

int main() {
	 int i, n, m, r, l, v;
	 for(scanf("%i",&n), i = 0; i < n; ++i)
		  scanf("%i",&A[i]);

	 create (0, n - 1, 0);

	 for(scanf("%i", &m), getchar(); m--;)
	 {
		  fgets(buffer, 100, stdin);
		  if(sscanf (buffer, "%i%i%i", &l, &r, &v) & 1)
		  {
				if(r >= l) update (0, n - 1, l, r, v, 0);
				else update (0, n - 1, l, n - 1, v, 0), update (0, n - 1, 0, r, v, 0);
		  }
		  else{
				if(r >= l) printf("%lld\n", get (0, n - 1, l, r, 0));
				else printf("%lld\n", min( get (0, n-1, l, n-1, 0), get (0, n-1, 0, r, 0)));
		  }
	 }
	 return 0;
}
