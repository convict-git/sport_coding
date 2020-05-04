#include         <bits/stdc++.h>
#pragma GCC      optimize ("Ofast")
#pragma GCC      optimize ("unroll-loops")
#pragma GCC      target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#define IOS      ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC     cout.precision (10); cout << fixed
#define bg(x)    "[ " << #x << " : " << x << " ]"
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;
const int N = 5555;
const int infi = (int)1e9;

int f[N][N];
vector < vector <int> > Adj;
int n, m;
int Par[N];
map <string, int> mpName, mpClub, mpParty;
map <int, string> dmpName, dmpClub, dmpParty;

int bfs (int s, int t) {
   fill (Par, Par + N, -1);
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

int nc, np, nn;
void init() {
   nc = 0;
   nn = 1005;
   np = 2010;
   Adj.assign(N, vector <int> ());
   mpName.clear();
   mpClub.clear();
   mpParty.clear();
   dmpName.clear();
   dmpClub.clear();
   dmpParty.clear();
   for (int i = 0; i < N; ++i)
      for (int j = 0; j < N; ++j)
         f[i][j] = 0;
}

void solve(int tc) {
   init();
   cin.ignore();
   cin.ignore();
   string st;
   while (true) {
      getline(cin, st);
      bool eoff = !cin;

      if (eoff || st[0] - 'A' == -65) {
         int s = 5553, t = 5554;
         for (auto vc : mpClub) {
            Adj[t].push_back(vc.y);
            Adj[vc.y].push_back(t);
            f[vc.y][t] = 1;
         }
         int total = (int)mpClub.size();

         for (auto vp : mpParty) {
            Adj[s].push_back(vp.y);
            Adj[vp.y].push_back(s);
            f[s][vp.y] = (total - 1)/2;
         }

         int flow = edmondsKarp(s, t);
         if (flow != total) cout << "Impossible\n";
         else {
            for (auto vc : mpClub) {
               for (int vn : Adj[vc.y]) {
                  if (vn == t) continue;
                  if (f[vc.y][vn] == 1) {
                     cout << dmpName[vn] << ' ' << dmpClub[vc.y] << '\n';
                     //break;
                  }
               }
            }
         }

         --tc;
         if (tc) cout << '\n';
         if (!tc) break;
         init();
         if (eoff) break;
      }
      else {
         stringstream ss(st);
         string name, party, club;
         ss >> name;
         assert(mpName.find(name) == mpName.end());
         mpName[name] = nn;
         dmpName[nn] = name;

         ss >> party;
         int vp;
         if (mpParty.find(party) == mpParty.end()) {
            mpParty[party] = np;
            vp = np;
            dmpParty[np] = party;
            ++np;
         } else {
            vp = mpParty[party];
         }
         Adj[nn].push_back(vp);
         Adj[vp].push_back(nn);
         f[vp][nn] = 1;

         int vc;
         while (ss >> club) {
            if (mpClub.find(club) == mpClub.end()) {
               mpClub[club] = nc;
               vc = nc;
               dmpClub[nc] = club;
               ++nc;
            }
            else {
               vc = mpClub[club];
            }
            Adj[nn].push_back(vc);
            Adj[vc].push_back(nn);
            f[nn][vc] = 1;
         }
         ++nn;
      }
   }
}

signed main() {
   int tc;
   cin >> tc;
   solve(tc);

   return EXIT_SUCCESS;
}

