#include         <bits/stdc++.h>
using namespace std;
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    " [ " << #x << " : " << (x) << " ]"
#define x        first
#define y        second

#define debug(args...) { \
   string _s = #args; replace(_s.begin(), _s.end(), ',', ' ');\
   stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); \
}
void err(istream_iterator<string> it) { it->empty();
   cerr << " (Line : " << __LINE__ << ")" << '\n';
}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << " [ " <<  *it << " : " << a  << " ] "<< ' ';
	err(++it, args...);
}

const int N = (int)1e6 + 10;

int rep[N], rnk[N], sz[N];
int n, correct, wrong;

void makeSet() {
   for(int i = 0; i < n; ++i)
      rep[i] = i, rnk[i] = 0, sz[i] =  1;
}

int findSet(int u) {
   int ru = u;
   while (ru != rep[ru])
      ru = rep[ru];

   while (u != rep[u]) {
      int tmp = rep[u];
      rep[u] = ru;
      u = tmp;
   }
   return ru;
}

void mergeSet(int u, int v) {
   int ru = findSet(u), rv = findSet(v);
   if (rnk[ru] > rnk[rv]) {
      rep[rv] = rep[ru];
      sz[ru] += sz[rv];
   }
   else {
      rep[ru] = rep[rv];
      sz[rv] += sz[ru];
   }

   if (rnk[ru] == rnk[rv]) {
      ++rnk[rv];
   }
}

void read() {
   cin >> n;
   correct = wrong = 0;
   makeSet();
   string st;
   cin.ignore();
   while (true) {
      getline(cin, st);
      if (st[0] == 0) {
         return;
      }
      stringstream ss(st);
      char ch;
      int u, v;
      ss >> ch >> u >> v;
      --u, --v;
      if (ch == 'c') {
         mergeSet(u, v);
      }
      else if (ch == 'q') {
         if (findSet(u) == findSet(v)) ++correct;
         else ++wrong;
      }
   }
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      read();
      cout << correct << ',' << wrong << '\n';
      if (tc) cout << '\n';
   }

   return EXIT_SUCCESS;
}

