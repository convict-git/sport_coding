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
#pragma GCC      optimize ("Ofast")
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
const int MAXN = 1e6 + 10;
int N, M, q, Ar[MAXN], scc = 0;
int edgeCount[MAXN] = {0};
map <int, pair <int, int> > mp;
int pr[MAXN], rnk[MAXN];
void createset (int x) {
   pr[x] = x;
   rnk[x] = 0;
}

int findset (int x) {
   while (x != pr[x]) x = pr[x];
   return x;
}

void merge (int x, int y) {
   int repx = findset (x);
   int repy = findset (y);
   if (rnk[repx] > rnk[repy])  {
      pr[repy] = repx;
   }
   else {
      pr[repx] = repy;
   }
   if (rnk[repx] == rnk[repy])
      ++rnk[repy];
}

int main() {
   IOS; PREC;
   cin >> N >> M;
   for (int i = 0; i < N; ++i) createset (i);

   for (int i = 0; i < M; ++i) {
      int u, v;
      cin >> u >> v;
      --u, --v;
      mp[i] = {u, v};
      ++edgeCount[u], ++edgeCount[v];
      merge (u, v);
   }
   for (int i = 0; i < N; ++i) {
      if (i == pr[i]) ++scc; //initially
   }
   cin >> q;
   for (int i = 0; i < q; ++i) {
      int t;
      cin >> t;
      --t;
      int u, v;
      u = mp[t].fi;
      v = mp[t].se;

      --edgeCount[u], --edgeCount[v];
      if (edgeCount[u] == 0 || edgeCount[v] == 0) {
         ++scc;
      }

      cout << scc << '\n';
   }

   return EXIT_SUCCESS;
}


