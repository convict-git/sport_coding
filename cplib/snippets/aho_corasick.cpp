#include      <bits/stdc++.h>
using namespace std;

// Aho Corasick library
// This library is created by Priyanshu Shrivastav (mr.convict)
// https://github.com/convict-git/sport_coding/blob/master/cplib/snippets/aho_corasick.cpp

#define cId(x) ((int) (x - 'a'))
/* This is offline, hence you need to add all strings first, and then call compute
 * In case you add another string after compute, there's no option then calling
 * compute ( )
 * */
class aho {
   public:
      static const int K = 26;
      // (there exist atmost m * k such node) (m = ∑|Si|, k = |∑| )
      struct Node { // can store lot of required information
         bool leaf;
         vector <int> nxt, go;
         int idx, parent;
         char pch;
         int b;

         Node (int id = 0, int p = -1, char ch = '$')
            : idx(id), parent(p), pch(ch) {
               leaf = false;
               b = 0;
               nxt.assign(K, -1);
               go.assign(K, -1);
            }
      };

      vector <Node> trie;
      vector <vector <int>> aut;
      vector <int> suff_link;
      vector <int> exit_link;
      vector <long long> node_value;

      aho () {
         trie.push_back(Node()); // root node
      }

      void add_string (const string &s, int &bval) {
         int cur = 0;
         for (char c : s) {
            if (trie[cur].nxt[cId(c)] == -1) {
               int nxt_idx = (int)trie.size();
               trie[cur].nxt[cId(c)] = nxt_idx;
               trie.push_back(Node(nxt_idx, cur, c));
            }
            cur = trie[cur].nxt[cId(c)];
         }
         trie[cur].leaf = true;
         trie[cur].b = bval;
      }

      void compute () {
         int sz = (int) trie.size();
         aut.assign(sz, vector <int> (K, -1));
         suff_link.assign(sz, -1);
         exit_link.assign(sz, -1);
         node_value.assign(sz, 0ll);

         /* initialize info for root node */
         suff_link[0] = 0;
         exit_link[0] = 0;

         queue <int> q;
         q.push(0);

         /* compute for all nodes in BFS style */
         while (!q.empty()) {
            int prv_idx = q.front();
            q.pop();
            for (int c = 0; c < K; ++c) {
               int nxt_idx = trie[prv_idx].nxt[c];
               if (nxt_idx != -1) {
                  /* set automation */
                  aut[prv_idx][c] = nxt_idx;

                  /* set suff_link */
                  suff_link[nxt_idx] = (prv_idx != 0 ? aut[suff_link[prv_idx]][c] : 0);

                  /* Update node value */
                  node_value[nxt_idx] +=
                     node_value[suff_link[nxt_idx]] + trie[nxt_idx].b;

                  int nxt_suff_idx = suff_link[nxt_idx];
                  /* set up exit links */
                  exit_link[nxt_idx] = (trie[nxt_suff_idx].leaf
                        ?  nxt_suff_idx : exit_link[nxt_suff_idx]);

                  q.push(nxt_idx);
               }
               else {
                  /* set automation */
                  aut[prv_idx][c] = (prv_idx != 0 ? aut[suff_link[prv_idx]][c] : 0);
               }
            }
         }
      }
};
