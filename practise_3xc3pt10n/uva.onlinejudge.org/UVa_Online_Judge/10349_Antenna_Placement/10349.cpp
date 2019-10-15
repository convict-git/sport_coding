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
const int N = 40 * 10;

vector <string> input;
bool vis[N];
int match[N];
vector < vector <int> > Adj;
int n, nl, nr; // first 0, ..., nl - 1 vertices in left nl, ..., nr - 1 in right
int mp[N];


void re_init() {
   for (int i = 0; i < n; ++i)
      vis[i] = false, match[i] = -1;
}

void init() {
   Adj.assign(N, vector <int> ());
   input.clear();
   for (int i = 0; i < N; ++i) mp[i] = -1;
}

inline void add_edge(int u, int v) {
   Adj[u].push_back(v);
}

bool augment(int u) {
   if (vis[u]) return false;
   vis[u] = true;

   for (int v : Adj[u]) {
      if (match[v] == -1 || augment(match[v])) {
         match[v] = u;
         return true;
      }
   }
   return false;
}

int MCBM() {
   assert (nl + nr == n);
   int mcbm = 0;

   for (int u = 0; u < nl; ++u) { // in left set
      fill(vis, vis + n, false);
      mcbm += augment(u);
   }
   return mcbm;
}

int h, w;
void read() {
   init();
   cin >> h >> w;
   string st;
   for (int i = 0; i < h; ++i) {
      cin >> st;
      input.push_back(st);
   }

   nl = 0, nr = 0;

   for (int i = 0; i < h; ++i) {
      for (int j = 0; j < w; ++j) {
         if (input[i][j] == '*') {
            mp[w * i + j] = ((i & 1)^(j & 1) ? nl++ : nr++);

            if (i != 0 && input[i - 1][j] == '*') {
               if ((i & 1)^(j & 1)) add_edge (mp[w * i + j], mp[w * (i - 1) + j]);
               else add_edge (mp[w * (i - 1) + j], mp[w * i + j]);
            }
            if (j != 0 && input[i][j - 1] == '*') {
               if ((i & 1)^(j & 1)) add_edge (mp[w * i + j], mp[w * i + j - 1]);
               else add_edge (mp[w * i + j - 1], mp[w * i + j]);
            }
         }
      }
   }
   n = nl + nr;
   re_init();

   int MIS = nl + nr - MCBM();
   cout << MIS << '\n'; // MIS
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   while (tc--) {
      read();
   }

   return EXIT_SUCCESS;
}


