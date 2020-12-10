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

const int Maxn = 3e5 + 10;
#define leftNode(x) (2 * x + 1)
#define rightNode(x) (2 * x + 2)
typedef long long ll;
int N, M;
ll Node[4 * Maxn], dp[Maxn];
int balls[Maxn];

// @Brief Does a sumimum range query on the segment tree in the range
// closed [`qryLeftRange`, `qryRightRange`]
ll sumInRange(
      int qryLeftRange,
      int qryRightRange,
      int leftRange = 0,
      int rightRange = N - 1,
      int curIdx = 0)
{
   // reach out of the required range
   if (qryLeftRange > rightRange or qryRightRange < leftRange) {
      return 0;
   }

   // inside the required range, return the cached result in the Node
   if (qryLeftRange <= leftRange and qryRightRange >= rightRange) {
      return Node[curIdx];
   }

   int midRange = (leftRange + rightRange) / 2;

   // find sumimum in left subtree
   ll leftVal = sumInRange(
         qryLeftRange,
         qryRightRange,
         leftRange,
         midRange,
         leftNode(curIdx));

   // find sumimum in right subtree
   ll rightVal = sumInRange(
         qryLeftRange,
         qryRightRange,
         midRange + 1,
         rightRange,
         rightNode(curIdx));

   // return sumimum of left and right subtree
   return leftVal + rightVal;
}

// @Brief Updates the segment tree at index `updAtIdx` with value `dp[updAtIdx]`
void updAtPoint(
      int updAtIdx,
      ll updVal,
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
      Node[curIdx] += updVal;
      return;
   }

   int midRange = (leftRange + rightRange) / 2;

   // update the left subtree
   updAtPoint(
         updAtIdx,
         updVal,
         leftRange,
         midRange,
         leftNode(curIdx));

   // update the right subtree
   updAtPoint(
         updAtIdx,
         updVal,
         midRange + 1,
         rightRange,
         rightNode(curIdx));

   // update the current node from left and right subtrees
   Node[curIdx] = Node[leftNode(curIdx)] + Node[rightNode(curIdx)];
}


void preproc()
{
}

void solve()
{
   int s, q;
   vector <int> req;
   vector <pair <int, int>> swaps;
   vector <pair <int, int>> queries;
   cin >> N >> M >> s >> q;
   for (int i = 0; i < M; ++i) {
      cin >> balls[i];
      req.push_back(balls[i]);
   }
   for (int i = 0; i < s; ++i) {
      int L, R;
      cin >> L >> R;
      req.push_back(L);
      req.push_back(R);
      swaps.push_back({L, R});
   }
   for (int i = 0; i < q; ++i) {
      int L, R;
      cin >> L >> R;
      req.push_back(L);
      req.push_back(R);
      queries.push_back({L, R});
   }

   sort(req.begin(), req.end());
   req.erase(unique(req.begin(), req.end()), req.end());

   auto idxComp = [&] (int idx) -> int {
      return (int)(lower_bound(req.begin(), req.end(), idx) - req.begin());
   };

   N = static_cast <int> (req.size());

   memset(Node, 0, sizeof(Node));

   for (int i = 0; i < M; ++i) {
      int idx = idxComp(balls[i]);
      updAtPoint(idx, 1);
   }

   for (int i = 0; i < s; ++i) {
      int Lidx = idxComp(swaps[i].first);
      int Ridx = idxComp(swaps[i].second);

      ll lValue = sumInRange(Lidx, Lidx);
      ll rValue = sumInRange(Ridx, Ridx);

      updAtPoint(Lidx, rValue - lValue);
      updAtPoint(Ridx, lValue - rValue);
   }

   for (int i = 0; i < q; ++i) {
      int Lidx = idxComp(queries[i].first);
      int Ridx = idxComp(queries[i].second);

      cout << sumInRange(Lidx, Ridx) << " \n"[i == q - 1];
   }
}

signed main()
{
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
