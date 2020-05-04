#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define x        first
#define y        second
using namespace std;

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

using pii = pair <int, int>;

const int N = (int)1e4;
const int infi = (int)1e9;

int f[N][N];
vector < vector <int> > Adj;
int n, m;
int Par[N];

map <string, int> mpName, mpClub, mpParty;
map <int, string> dmpName, dmpClub, dmpParty;
vector < vector <int> > clubList;
vector <int> ofParty;

int bfs (int s, int t) {
   fill (Par, Par + n, -1);
   Par[s] = -2;

   queue <pii> Q;
   Q.push(pii(s, infi));

   while (!Q.empty()) {
      pii tmp = Q.front();
      Q.pop();
      int u = tmp.x, flow = tmp.y;

      for (int v : Adj[u]) {
         if (Par[v] == -1 && f[u][v]) {
            Par[v] = u;
            int newFlow = min(flow, f[u][v]);
            if (v == t) {
               return newFlow;
            }
            Q.push(pii(v, newFlow));
         }
      }
   }
   return 0;
}

int edmondsKarp(int s, int t) {
   int flow = 0;
   int newFlow;

   while ((newFlow = bfs (s, t))) {
      flow += newFlow;
      int cur = t;
      while (cur != s) {
         int prv = Par[cur];
         f[prv][cur] -= newFlow;
         f[cur][prv] += newFlow;
         cur = prv;
      }
   }
   return flow;
}

inline void addEdge (int u, int v, int flow) {
   Adj[u].push_back(v);
   Adj[v].push_back(u);
   f[u][v] = flow;
}


int nc, np, nr, s, t;
void init () {
   nc = np = nr = 0;
   mpName.clear(), dmpName.clear();
   mpClub.clear(), dmpClub.clear();
   mpParty.clear(), dmpParty.clear();
   clubList.assign(1000, vector <int> ());
   ofParty.assign(1000, -1);

}

void solve(int tc) {
   string st, name, party, club;
   while (tc--) {
      init();
      while (getline(cin, st)) {
         if (st.empty()) break;
         stringstream ss (st);
         ss >> name >> party;
         mpName[name] = nr;
         dmpName[nr] = name;

         if (mpParty.find(party) == mpParty.end()) {
            mpParty[party] = np;
            dmpParty[np] = party;
            ++np;
         }

         ofParty[nr] = mpParty[party];

         while (ss >> club) {
            if (mpClub.find(club) == mpClub.end()) {
               mpClub[club] = nc;
               dmpClub[nc] = club;
               ++nc;
            }
            clubList[nr].push_back(mpClub[club]);
         }
         ++nr;
      }

      //index => name = i, party = nr + i, club = nr + np + i
      n = nr + nc + np + 2;
      //debug(nc, nr, np, n);
      s = n - 2, t = n - 1;

      Adj.assign(n, vector <int> ());

      for (int i = 0; i < n; ++i)
         for (int j = 0; j < n; ++j)
            f[i][j] = 0;

      for (auto el : mpClub) addEdge(el.y + nr + np, t, 1);

      for (auto el : mpParty) addEdge(s, el.y + nr, (nc - 1)/2);

      for (int i = 0; i < nr; ++i) {
         addEdge(ofParty[i] + nr, i, 1);

         for (int v : clubList[i]) {
            addEdge(i, v + nr + np, 1);
         }
      }


      int flow = edmondsKarp(s, t);
      //debug(flow, s, t, nc);
      if (flow != nc) {
         cout << "Impossible.\n";
      }
      else {
         for (auto el : mpClub) {
            int u = el.y + np + nr;
            for (int v : Adj[u]) {
               if (v == t) continue;
               if (f[u][v] == 1) cout << dmpName[v] << ' ' << dmpClub[u - np - nr] << '\n';
            }
         }
      }
      if (tc) cout << '\n';
   }
}

signed main() {
   IOS; PREC;
   int tc;
   cin >> tc;
   string st;
   getline(cin, st);
   getline(cin, st);
   solve(tc);

   return EXIT_SUCCESS;
}

