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
int vis[mxn], d[mxn], who[mxn], eval[mxn], mp[mxn], x[mxn], sz[mxn];
vector <Edge> edges;
set <Edge> Espan;
struct co {
   int rep;
   vector <Edge> Eext;
   bool operator < (const co &o) const  {
      return Eext.size() < o.Eext.size(); // graphs before tree (graph is non tree)
   }
};
co S[mxn];

void reset() {
   cc = 0, loss=0;
   Espan.clear(), edges.clear();
   for(int i = 0; i < mxn; ++i) {
      S[i].Eext.clear(), g[i].clear();
      sz[i]=who[i]=vis[i]=d[i]=x[i]=mp[i]=0; // d is old deg , x is new deg
   }
   for (int i = 0; i < mxn; ++i) {
      eval[i] = 0;
   }
}

void preproc() {
}

void dfs (int u, int rep) { // spanning tree
   who[u] = rep;
   ++sz[rep];
   for (auto vp : g[u]) {
      int v = vp.x, e = vp.y;
      if (!vis[v]) {
         vis[v]=1;
         eval[e] = 1; // mark as spanning edge
         Espan.insert({{u, v}, -1});
         dfs(v, rep);
      }
   }
}

class cmp {
   public:
      bool operator() (const int &u, const int &v) {
         return S[mp[u]].Eext.size() < S[mp[v]].Eext.size();
      }
};

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

   priority_queue <int, vector <int>, cmp> pq_graph;
   vector <int> trees;

   for (int i = 0; i < cc; ++i) {
      if (!S[i].Eext.empty()) { // graph
         pq_graph.push(S[i].rep);
      }
      else { // tree
         trees.push_back(S[i].rep);
      }
   }
   sort(trees.begin(), trees.end(), [&] (int p, int q) { return sz[trees[p]] < sz[trees[q]]; });

   while ((int)pq_graph.size() + (int)trees.size() != 1){
      if (pq_graph.size() >= 2 && (int)S[mp[pq_graph.top()]].Eext.size() >= 2) {
         debug("start case0");
         int repC1 = pq_graph.top();
         co &C1 = S[mp[repC1]];
         pq_graph.pop();

         int repC2 = pq_graph.top();
         co &C2 = S[mp[repC2]];
         pq_graph.pop();

         Edge E1 = C1.Eext.back();
         C1.Eext.pop_back();
         int u1 = E1.x.x, v1 = E1.x.y;

         Edge E2 = C2.Eext.back();
         C2.Eext.pop_back();
         int u2 = E2.x.x, v2 = E2.x.y;

         Espan.insert({{u1, u2}, -1}); // spanning
         C1.Eext.push_back({{v1, v2}, -1}); // ext
         for (Edge E : C2.Eext) C1.Eext.push_back(E);
         loss += 0;
         pq_graph.push(repC1);
         debug("end case0");
      }
      // Case x - G T A
      else if (!pq_graph.empty() and !trees.empty() and sz[trees.back()] >= 2) {
         int repC1 = pq_graph.top();
         co &C1 = S[mp[repC1]];
         pq_graph.pop();

         Edge E1 = C1.Eext.back();
         C1.Eext.pop_back();
         int u1 = E1.x.x, v1 = E1.x.y;

         int repC2 = trees.back();
         trees.pop_back();

         int u2 = repC2, v2 = g[repC2][0].x;
         Espan.erase({{u2, v2}, -1});
         Espan.erase({{v2, u2}, -1});

         pq_graph.push(repC1);
         loss += 0;
         debug("end case2");
      }
      else if (!pq_graph.empty() and (int)trees.size() >= 2) {
         debug("case1");
         int repC1 = pq_graph.top();
         int Sidx = mp[repC1]; // index to S
         co &C1 = S[Sidx];
         pq_graph.pop();

         Edge E1 = C1.Eext.back();
         int u1 = E1.x.x, v1 = E1.x.y;
         C1.Eext.pop_back();

         int repC2 = trees.back();
         trees.pop_back();
         int repC3 = trees.back();
         trees.pop_back();

         Espan.insert({{u1, repC2}, -1});
         Espan.insert({{v1, repC3}, -1});
         loss += 2;

         if (C1.Eext.empty()) { // Tree
            trees.push_back(repC1);
         }
         else {
            pq_graph.push(repC1);
         }
         debug("end case1");
      }
      // Case IV - T T p4
      else if (trees.size() >= 2){
         debug("case4");
         int repC1 = trees.back();
         trees.pop_back();
         int repC2 = trees.back();
         trees.pop_back();

         Espan.insert({{repC1, repC2}, -1});
         trees.push_back(repC1);
         loss += 2;
         debug("end case4");
      }
      // Case II - G T p2
      else if (!pq_graph.empty() and !trees.empty()){
         debug("case2");
         int repC1 = pq_graph.top();
         pq_graph.pop();

         int repC2 = trees.back();
         trees.pop_back();

         Espan.insert({{repC1, repC2}, -1});
         pq_graph.push(repC1);
         loss += 2;
         debug("end case2");
      }
   }

   vector <Edge> finalEdges;
   if (!pq_graph.empty()) {
      int repC1 = pq_graph.top();
      co &C1 = S[mp[repC1]];
      pq_graph.pop();
      for (Edge E : C1.Eext) finalEdges.push_back(E);
   }
   for (Edge E : Espan) finalEdges.push_back(E);
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
