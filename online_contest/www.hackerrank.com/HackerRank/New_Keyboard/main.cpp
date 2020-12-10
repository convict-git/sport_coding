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

void preproc() {
}

struct Node {
   string s = "";
   int nxtPtr = -1, prvPtr = -1;
};

const int mxn = 1e6 + 10;
vector <Node> store;

inline int backspace (int curNode) {
   if (!store[curNode].s.empty()) {
      // remove from this string itself
      store[curNode].s.pop_back();
      return curNode;
   }
   else if (store[curNode].prvPtr != -1)  {
      // something exist before
      int prvNode = store[curNode].prvPtr;
      int nxtNode = store[curNode].nxtPtr;
      store[prvNode].nxtPtr = nxtNode;
      return backspace(prvNode);
   }
   else {
      // Do nothing
      return curNode;
   }
}

void solve() {
   store.push_back(Node());
   int curNode = 0, startNode = 0, lastNode = 0;
   int numLock = 1; // you can use the numbers

   string inp;
   cin >> inp;

   for (char c : inp) {
      if (c == '<') { // Home
         curNode = (int)store.size();
         store.push_back(Node());
         store[curNode].nxtPtr = startNode;
         store[startNode].prvPtr = curNode;

         startNode = curNode;
      }
      else if (c == '>') { // End
         curNode = (int)store.size();
         store.push_back(Node());
         store[lastNode].nxtPtr = curNode;
         store[curNode].prvPtr = lastNode;

         lastNode = curNode;
      }
      else if (c == '*') { // backspace
         curNode = backspace(curNode);
      }
      else if (c == '#') { // NumLock
         numLock ^= 1;
      }
      else {
         if (!isdigit(c) or (isdigit(c) and numLock)) {
            store[curNode].s.push_back(c);
         }
      }
   }

   curNode = startNode;
   while (curNode != -1) {
      cout << store[curNode].s;
      curNode = store[curNode].nxtPtr;
   }
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  // cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}
