// Hack it and have it ;) //
/*author* Priyanshu Shrivastav (from IIT Palakkad) *
 * *_ __ ___  _ ______ ___  _ ____   ___  ___| |_  *
 * | '_ ` _ \| '__/ __/ _ \| '_ \ \ / / |/ __| __| *
 * | | | | | | | | (_| (_) | | | \ V /| | (__| |_  *
 * |_| |_| |_|_|(_)___\___/|_| |_|\_/ |_|\___|\__| *
When I wrote this, only God and I understood what I was doing
 ** * * * * * * * Now, only God knows!* * * * * * */

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

typedef long long ll;
const int Maxn = 1e6 + 10;
const int LOGN = 21;
#define T(x) (1 << (x))
#define leftNode(x) (2*x + 1)
#define rightNode(x) (2*x + 2)

int N, M;
ll dp[Maxn],
   cost[Maxn],
   Node[4 * Maxn];

// @Brief Creates a segment tree
void create (
      int leftRange = 0,
      int rightRange = N - 1,
      int curIdx = 0)
{
   // leaf
   if (leftRange == rightRange) {
      Node[curIdx] = dp[leftRange];
      return;
   }
   int midRange = (leftRange + rightRange) / 2;
   // create the left subtree
   create(
         leftRange,
         midRange,
         leftNode(curIdx));

   // create the right subtree
   create(
         midRange + 1,
         rightRange,
         rightNode(curIdx));

   // write on the current node
   Node[curIdx] = min(Node[leftNode(curIdx)], Node[rightNode(curIdx)]);
}

// @Brief Does a minimum range query on the segment tree in the range
// closed [`qryLeftRange`, `qryRightRange`]
ll minInRange(
      int qryLeftRange,
      int qryRightRange,
      int leftRange = 0,
      int rightRange = N - 1,
      int curIdx = 0)
{
   // reach out of the required range
   if (qryLeftRange > rightRange or qryRightRange < leftRange) {
      return LLONG_MAX;
   }

   // inside the required range, return the cached result in the Node
   if (qryLeftRange <= leftRange and qryRightRange >= rightRange) {
      return Node[curIdx];
   }

   int midRange = (leftRange + rightRange) / 2;

   // find minimum in left subtree
   ll leftVal = minInRange(
         qryLeftRange,
         qryRightRange,
         leftRange,
         midRange,
         leftNode(curIdx));

   // find minimum in right subtree
   ll rightVal = minInRange(
         qryLeftRange,
         qryRightRange,
         midRange + 1,
         rightRange,
         rightNode(curIdx));

   // return minimum of left and right subtree
   return min(leftVal, rightVal);
}

// @Brief Updates the segment tree at index `updAtIdx` with value `dp[updAtIdx]`
void updAtPoint(
      int updAtIdx,
      int leftRange = 0,
      int rightRange = N - 1,
      int curIdx = 0)
{
   // reach out of the required index
   if (updAtIdx > rightRange or updAtIdx < leftRange) {
      return;
   }

   // at the required index, update that Node
   if (leftRange == rightRange and updAtIdx == leftRange) {
      Node[curIdx] = dp[updAtIdx];
      return;
   }

   int midRange = (leftRange + rightRange) / 2;

   // update the left subtree
   updAtPoint(
         updAtIdx,
         leftRange,
         midRange,
         leftNode(curIdx));

   // update the right subtree
   updAtPoint(
         updAtIdx,
         midRange + 1,
         rightRange,
         rightNode(curIdx));

   // update the current node from left and right subtrees
   Node[curIdx] = min(Node[leftNode(curIdx)], Node[rightNode(curIdx)]);
}

void preproc()
{
}

void solve()
{
   cin >> N >> M;
   ll prefSum = 0;
   vector <pair <ll, ll>> store;

   for (int pos = 0, lstPos = 0; pos < N; ++pos) {
      cin >> cost[pos];
      // if on first or last position, always consider
      if (pos == 0 or pos == N - 1) {
         cost[pos] = 0;
         prefSum += pos - lstPos;
         store.push_back({prefSum, 0});
         lstPos = pos;
      }
      // if cost is non-zero, then consider
      if (cost[pos]) {
         prefSum += pos - lstPos;
         store.push_back({prefSum, cost[pos]});
         lstPos = pos;
      }
   }

   // now completely forget about the past
   N = static_cast <int> (store.size());
   for (int pos = 0; pos < N; ++pos) {
      dp[pos] = (pos ? LLONG_MAX : 0ll);;
   }

   // initialize the segment tree
   create();

   auto diffCalcBtwIdx = [&] (int x, int y) -> ll {
      return store[y].first - (x ? store[x].first : 0ll);
   };

   // now calculate and upd on the fly
   for (int pos = 0; pos < N; ++pos) {
      int lstPos = pos;

      // doing binary search to find lstPos
      for (int d = LOGN; d >= 0; --d) {
         int newLeft = lstPos - T(d) + 1;
         if (newLeft >= 0 and diffCalcBtwIdx(newLeft, pos) <= M) {
            lstPos = newLeft - 1;
         }
      }
      ++lstPos;
      // now lstPos is where is the left most possible index where condition holds

      ll minPosCost = minInRange(lstPos, pos);

      // if min received is reasonable, then update
      if (minPosCost != LLONG_MAX) {
         dp[pos] = minPosCost + store[pos].second;
         updAtPoint(pos);
      }
   }

   // answer will be on dp[N - 1]
   cout << (dp[N - 1] == LLONG_MAX ? -1 : dp[N - 1]) << '\n';
}
#undef T
#undef leftNode
#undef rightNode

signed main()
{
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}