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
#ifndef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

// geometry part
constexpr double eps = 1e-9;
inline bool isZero(double x) { return fabs(x) < eps; }
inline bool isZero(long long x) { return x == 0ll; }
struct pt {
   long long x, y;
   pt(){}
   pt(long long _x, long long _y):x(_x), y(_y){}
   pt operator+(const pt &o) const { return pt(x + o.x, y + o.y); }
   pt operator-(const pt &o) const { return pt(x - o.x, y - o.y); }
   long long cross(const pt &o) const { return x * o.y - y * o.x; }
   long long cross(const pt & a, const pt & b) const { return (a - *this).cross(b - *this); }
   long long dot(const pt &o) const { return x * o.x + y * o.y; }
   long long dot(const pt &a, const pt &b) const { return (a - *this).dot(b - *this); }
   long long sqrLen() const { return this->dot(*this); }
   bool operator < (const pt &o) const { // left or down first
      return x < o.x || (isZero(x - o.x) && y < o.y);
   }
   bool operator == (const pt &o) const { // left or down first
      return isZero(x-o.x) && isZero(y-o.y);
   }
   //// Note c.x > a.x is an assumption in all functions below
   bool aboveLine(const pt &a, const pt &c) {                /*   b   */
      return (c.x-a.x)*(y-c.y) + (c.y-a.y)*(c.x-x) > 0;     /*  / \  */
   }                                                        /* a   c */
   bool belowLine(const pt &a, const pt &c) {               /* a   c */
      return (c.x-a.x)*(y-c.y) + (c.y-a.y)*(c.x-x) < 0;     /*  \ /  */
   }                                                        /*   b   */
   bool onLine(const pt &a, const pt &c) {
      return isZero((c.x-a.x)*(y-c.y) + (c.y-a.y)*(c.x-x)); /* a-b-c */
   }
   friend ostream& operator << (ostream &os, const pt& p) {
      os << "(" << p.x << "," << p.y << ")";
      return os;
   }
   friend istream& operator >> (istream &is, pt& p) {
      is >> p.x >> p.y;
      return is;
   }
};
inline long long ABS (long long x) { return x > 0 ? x : -1ll*x; }

struct CH {
   vector <pt> chVec; // point of convexHull
   pt A, B; // left-down and right-up
   int bidx; // index of B in chVec
};
vector <CH> layers; // concentric layers from inside to outside
set <pt> pts; // set of original N given points
int n, q;

// convexHull, smallest polygon such that all points lie inside or on it
// no triplet exist which are collinear, clockwise order of points in res
CH grahamScan (vector <pt> &a) { // in O(NlogN), N is the number of points given
   CH hull;
   sort(a.begin(), a.end()); // sort based on left-most-down
   vector <pt> up, down;
   const pt A = a.front(), B = a.back(); // A is left-most-down and B is right-most-up
   hull.A = A, hull.B = B;
   up.push_back(A);
   down.push_back(A);
   for (int i = 1; i < (int)a.size(); ++i) {
      pt cur = a[i];
      // create the upper part of the convexhull
      if (i == (int)a.size()-1 || a[i].aboveLine(A, B))  { // up updates
         while (up.size() >= 2 &&
               !up[(int)up.size()-1].aboveLine(up[(int)up.size()-2], cur))
            up.pop_back();
         up.push_back(cur);
      }
      // create the lower part of the convexhull
      if (i == (int)a.size()-1 || a[i].belowLine(A, B)) { // down updates
         while (down.size() >= 2 &&
               !down[(int)down.size()-1].belowLine(down[(int)down.size()-2], cur))
            down.pop_back();
         down.push_back(cur);
      }
   }
   hull.bidx = (int)up.size() - 1; // B is the last pt in up
   // insert the up part of the hull in increasing order of their x
   for (int i = 0; i < (int)up.size(); ++i) {
      hull.chVec.push_back(up[i]);
      pts.erase(up[i]); // now used in one of the hulls
   }
   // insert the down part of hull in decreasing order of their x
   // to maintain clockwise order points in hull
   for (int i = (int)down.size()-2; i > 0; --i) { // skip A (first el)and B (lst el)
      hull.chVec.push_back(down[i]);
      pts.erase(down[i]); // now used in one of the hulls
   }
   return hull;
}
bool pointInTriangle(pt a, pt b, pt c, pt point){
    long long s1 = ABS(a.cross(b, c));
    long long s2 = ABS(point.cross(a, b)) + ABS(point.cross(b, c)) + ABS(point.cross(c, a));
    return s1 == s2;
}
// NOTE : lies strictly inside the polygon (Not on polygon)
bool liesStInside(pt qry, int layIdx) { // log2(N), N is the size of convex polygon
   // debug(layIdx);
   CH &hull = layers[layIdx];
   pt A = hull.chVec.front(); // left-down most
   // qry.x should be in the range [A.x, infi)
   if (qry.x < A.x) {
      //cerr << "before A\n";
      return false;
   }
   pt Ad = hull.chVec[1]; // second left-down most
   pt B = hull.chVec.back(); //  last point clockwise
   // shouldn't lie in first and last zone
   if (qry.aboveLine(A, Ad) || qry.belowLine(A, B)) {
      //cerr << "Lies in the first or last zone\n";
      return false;
   }
   // shoudn't lie on the first and last line as well
   if (qry.onLine(A, Ad) || qry.onLine(A, B)) {
      //cerr << "Lies on the first or last line\n";
      return false;
   }
   // now find the right zone by binary searching
   // there exists an i in [1..n-2] such that qry lies in triangle {A, pi, p(i+1)}
   // all j <= i, qry will belowLine for (A, pj)
   // and all j > i, qry will aboveLine for (A, pj),
   // hence binary search property, hence find the max i, ST qry.belowLine(A, pi)
   int L = 1, H = (int)hull.chVec.size()-2;
   while (L <= H) {
      int g = (L+H)/2;
      if (qry.belowLine(A, hull.chVec[g])) L=g+1;
      else H=g-1;
   }
   pt C = hull.chVec[H], D = hull.chVec[H+1];
   //cerr << "C and D : " << C << ' ' << D << "\n";
   // now we know the region, but
   // first of all it shouldn't lie on the line (C,D)
   if (qry.onLine(C, D)) {
      //cerr << "one line CD\n";
      return false;
   }
   // and want to make sure that it lies inside the triange {A, C, D}
   // if pi and p(i+1) lies below horizon then qry should make aboveLine
   // else belowLine
   if (pointInTriangle(A, C, D, qry)) {
      //cerr << "Inside triangle\n";
      return true;
   }
   else {
      //cerr << "outside triangle\n";
      return false;
   }
}

void reset() {
   layers.clear();
   pts.clear();
}

void preproc() {
}

void solve() { // O(N*N*log2N + Q*log2N*log2N)
   reset();
   // input
   cin >> n >> q;
   for (int i = 0, X, Y; i < n; ++i) {
      cin >> X >> Y;
      pts.insert(pt(X, Y));
      cerr << X << ' ' << Y << "\n";
   }
   // find layers of convex hulls
   while ((int)pts.size() > 2) { // O(N * N log2N), should be quite less than that
      vector <pt> lft(pts.begin(), pts.end());
      CH hull = grahamScan(lft);
      int sz = (int)hull.chVec.size();
      if (sz > 2) {
         /*
         for (int i = 0; i < sz; ++i) {
            cerr << hull.chVec[i].x << ' ' << hull.chVec[i].y << ' '
               << hull.chVec[(i+1) % sz].x << ' ' << hull.chVec[(i+1) % sz].y << '\n';
         }
         */
         layers.push_back(grahamScan(lft));
      }
   }
   // reverse(layers.begin(), layers.end());
   int mxLayer = (int)layers.size();

  //  debug(mxLayer);
   /*
   // see the layers
   for (int i = 0; i < mxLayer; ++i) {
      cerr << "#Layer:" << i << " - ";
      cerr << "[";
      for (int j = 0; j < (int)layers[i].chVec.size(); ++j){
         if (j) //cerr << ", ";
         cerr << "(" << layers[i].chVec[j].x << ", " << layers[i].chVec[j].y << ")";
      }
      cerr << "]\n";
   }
   */
   // for each query
   // do binary search to find the cocentric convex hulls it is in inside
   while (q--) { // O(Q * log2N * log2N)
      int X, Y;
      cin >> X >> Y;
      pt qry(X, Y);
      //cerr << "Query : " << qry << '\n';
      int L = 0, H = mxLayer-1;
      while (L <= H) {
         int g = (L+H)/2;
         if (liesStInside(qry, g)) L=g+1;
         else H=g-1;
      }
      cout << H+1 << '\n';
   }
   return;
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    solve();
  }
  return EXIT_SUCCESS;
}

