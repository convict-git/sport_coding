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
#define PREC     cin.tie (NULL); cout.precision (10); cout << fixed;
using namespace std;
int warnscanf_shit;
typedef int64_t ll;
typedef uint64_t ull; const int mod = 1e9 + 7; const int maxn = 1e3 + 10;
int n, r, u, ct, sm;
int fq[maxn] = {0};
int A[maxn] = {0};

void solve () {
   scanf ("%i%i", &n, &r);
   ct = 0;
   for (int i = 0; i < n; ++i) {
      scanf ("%i", &u);
      A[i] = u;
      if (u == 1) {
         ++ct;
         for (int j = max (0, i - r + 1); j <= min (n - 1, i + r - 1); ++j)
            fq[j] += 1;
      }
   }
   sm = ct;
   for (int i = 0; i < n; ++i) {
      if (fq[i] == 0) {
         printf ("-1\n");
         return;
      }
      if (A[i] == 1) {
         for (int j = max (0, i - r + 1); j <= min (n - 1, i + r - 1); ++j) {
            if (fq[j] == 0) {
               printf ("-1\n");
               return;
            }
            if (fq[j] == 1)
               break;
            if (j == min (n - 1, i + r - 1)) {
               for (int k = max (0, i - r + 1); k <= min (n - 1, i + r - 1); ++k)
                  fq[k] -= 1;
               sm -= 1;
            }
         }
      }
   }
   if (ct) printf ("%i\n", sm);
   else printf ("-1\n");
}

int main() {
   //IOS; PREC;
#ifdef CONVICTION
   if(!freopen ("input1", "r", stdin)) return EXIT_FAILURE;
#endif
   solve ();

   return EXIT_SUCCESS;
}
