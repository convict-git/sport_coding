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
typedef pair <int, int> pii;

const int maxn = 1e5 + 10;
const int _mod = 1e9 + 7;
const int mxn = 101;

int n;
int Ar[mxn];
int frq[mxn] = {0};

int main() {
   //IOS; PREC;
   scanf ("%i", &n);
   for (int i = 0; i < n; ++i) {
      scanf ("%i", Ar + i);
      ++frq [Ar[i]];
   }

   int t1 = 0, t3 = 0;
   for (int i = 0; i < mxn; ++i) {
      if (frq[i] == 1) ++t1;
      else if (frq[i] > 2) ++t3;
   }

   if (!(t1 & 1) || (t1 & 1 && t3 != 0)) {
      printf ("YES\n");
      int f = t1&1;
      t1 >>= 1;
      if (f) t3 = 1;

      for (int i = 0; i < n; ++i) {
         int ct = frq[Ar[i]];
         if (ct == 1 && t1) printf("A"), --t1;
         else if (ct == 1 && !t1) printf("B");
         else if ((ct > 2) & f & t3) printf("A"), --t3;
         else printf("B");
      } printf ("\n");
   }

   else printf ("NO\n");
   return EXIT_SUCCESS;
}
