#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (10); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

#define Edge pair <pair <int ,int>, int>
#define x first
#define y second

const int mxn =1e6+10;
int n, m;
int cc;
long long loss;
vector <pair <int, int>> g[mxn]; // adj list
int vis[mxn], d[mxn], who[mxn], eval[mxn], mp[mxn], x[mxn];
vector <Edge> edges, Espan;
struct co {
   int rep;
   vector <Edge> Eext;
   bool operator < (const co &o) const  {
      return Eext.size() > o.Eext.size(); // graphs before tree (graph is non tree)
   }
};
co S[mxn];

void reset() {
   cc = 0, loss=0;
   Espan.clear(), edges.clear();
   for(int i = 0; i < n; ++i) {
      S[i].Eext.clear(), g[i].clear();
      who[i]=vis[i]=d[i]=x[i]=mp[i]=0; // d is old deg , x is new deg
   }
   for (int i = 0; i < m; ++i) {
      eval[i] = 0;
   }
}

void preproc() {
}

void dfs (int u, int rep) { // spanning tree
   who[u] = rep;
   for (auto vp : g[u]) {
      int v = vp.x, e = vp.y;
      if (!vis[v]) {
         vis[v]=1;
         eval[e] = 1; // mark as spanning edge
         Espan.push_back({{u, v}, e});

         dfs(v, rep);
      }
   }
}

void solve() {
   cin >> n >> m;
   reset();
   // input // u <-> v multiple edges
   for (int e = 0, u, v; e < m; ++e) {
      cin >> u >> v;
      --u, --v;
      edges.push_back({{u, v}, e});
      g[u].push_back({v, e});
      g[v].push_back({u, e});
      ++d[u], ++d[v];
   }
   // dfs from every node
   // find all connected components
   for (int u = 0; u < n; ++u) { // O(N + M)
      if (!vis[u]) {
         vis[u]=1;
         dfs(u, u);
         mp[u] = cc;
         S[cc].rep = u; // eliminates use of dmp
         ++cc;
      }
   }
   // classify edges
   for (int e = 0; e < m; ++e) {
      if (!eval[e]) { // non-spanning edges only
         Edge E = edges[e];
         int u = E.x.x; // , v = E.x.y; // end points of edge
         int repU = who[u]; // rv = who[v]; assert(ru == rv);
         int ccIdx = mp[repU];
         S[ccIdx].Eext.push_back(E);
      }
   }
   // sort , takes non-trees first and trees then
   sort(S, S+cc); // sorted, graphs are before trees

   deque <co> deqS; // front has graphs and back has trees
   for (int i = 0; i < cc; ++i) {
      deqS.push_back(S[i]);
   }
   // for (int i = 0; i < cc; ++i){ debug(i, S[i].rep, S[i].Es); }

   // create graph
   while ((int)deqS.size() != 1)  { // |deqS| >= 1
      // flow , size == 2 , > 2
      co &C1 = deqS.front(); // keep the reference to make change here itself
      // deqS.pop_front(); Only pop if after merging we have tree
      co C2 = deqS.back();
      deqS.pop_back();

      // Case I // C1 is graph, C2 is tree, and possible to get C3 (a tree)
      if (!C1.Eext.empty() and C2.Eext.empty() and
            (int)deqS.size() >= 2 and deqS.back().Eext.empty()) {
         // graph and two trees if Possible
         loss += 2;
         co C3 = deqS.back();
         deqS.pop_back();
         // confirmed graph and two trees
         Edge E1 = C1.Eext.back(); C1.Eext.pop_back();
         int u1 = E1.x.x, v1 = E1.x.y;

         int repC2 = C2.rep, repC3 = C3.rep;
         Espan.push_back({{u1, repC2}, -1});
         Espan.push_back({{v1, repC3}, -1});

         if (C1.Eext.empty()) { // C1 is now a tree
            deqS.push_back(C1); // insert back as tree
            deqS.pop_front();   // remove the graph
         }
      }
      else { // two components
         if (!C1.Eext.empty() and !C2.Eext.empty()) { // graph and graph
            loss += 0;
            Edge E1 = C1.Eext.back();
            int u1 = E1.x.x, v1 = E1.x.y;
            C1.Eext.pop_back();

            Edge E2 = C2.Eext.back();
            int u2 = E2.x.x, v2 = E2.x.y;
            C2.Eext.pop_back();

            Espan.push_back({{u1, u2}, -1}); // one in spanning
            C1.Eext.push_back({{v1, v2}, -1}); // one in extraneous

            for (Edge E : C2.Eext) C1.Eext.push_back(E);
         }
         else { // graph-tree or tree-tree
            loss += 2;
            int repC1 = C1.rep;
            int repC2 = C2.rep;
            Espan.push_back({{repC1, repC2}, -1}); // will be in spanning
            // save graph for later if C1 is graph at all
         }
      }
   }
   assert((int)deqS.size() == 1);
   co &lastComp = deqS.back();

   vector <Edge> finalEdges;
   for (Edge E : Espan) finalEdges.push_back(E);
   for (Edge E : lastComp.Eext) finalEdges.push_back(E);

   for (Edge E : finalEdges) ++x[E.x.x], ++x[E.x.y];
   long long diff=0;
   for (int i = 0; i < n; ++i) {
      diff += abs(x[i]-d[i]);
   }
   assert(loss == diff);
   cout << loss << ' ' << finalEdges.size() << '\n';
   for (Edge E : finalEdges) {
      cout << E.x.x+1 << ' ' << E.x.y+1 << '\n';
   }
   return;
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
   //  cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
