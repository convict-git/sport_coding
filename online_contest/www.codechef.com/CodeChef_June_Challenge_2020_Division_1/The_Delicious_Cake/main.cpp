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

// geometry part
constexpr double eps = 1e-9;
inline bool isZero(double x) { return fabs(x) < eps; }
inline bool isZero(long long x) { return x == 0ll; }
struct pt {
   double x, y;
   pt(){}
   pt(double _x, double _y):x(_x), y(_y){}
   pt operator+(const pt &o) const { return pt(x + o.x, y + o.y); }
   pt operator-(const pt &o) const { return pt(x - o.x, y - o.y); }
   double cross(const pt &o) const { return x * o.y - y * o.x; }
   double cross(const pt & a, const pt & b) const { return (a - *this).cross(b - *this); }
   double dot(const pt &o) const { return x * o.x + y * o.y; }
   double dot(const pt &a, const pt &b) const { return (a - *this).dot(b - *this); }
   double sqrLen() const { return this->dot(*this); }
   bool operator < (const pt &o) const { // left or down first
      return x < o.x || (isZero(x - o.x) && y < o.y);
   }
   bool operator == (const pt &o) const { // left or down first
      return isZero(x-o.x) && isZero(y-o.y);
   }
   //// Note c.x > a.x is an assumption in below two functions
   bool aboveLine(const pt &a, const pt &c) {                /*   b   */
      return (c.x-a.x)*(y-c.y) + (c.y-a.y)*(c.x-x) > 0;     /*  / \  */
   }                                                        /* a   c */
   bool belowLine(const pt &a, const pt &c) {               /* a   c */
      return (c.x-a.x)*(y-c.y) + (c.y-a.y)*(c.x-x) < 0;     /*  \ /  */
   }                                                        /*   b   */
   bool onLine(const pt &a, const pt &c) {
      return isZero((c.x-a.x)*(y-c.y) + (c.y-a.y)*(c.x-x)); /* a-b-c */
   }
   bool pointInTriangle(const pt &a, const pt &b, const pt &c) {
      return isZero(fabs(this->cross(a, b)) + fabs(this->cross(b, c)) + fabs(this->cross(c, a)) - fabs(a.cross(b, c))); // area of triangle should be same
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

// ConvexHull structure
struct CH {
   vector <pt> chVec; // point of convexHull
   pt A, B; // left-down and right-up, AB makes the diameter
   friend ostream& operator << (ostream &os, const CH& hull) {
      os << "Size of Hull : " << hull.chVec.size() << "\n";
      os << "Diameter of hull = A :" << hull.A << ' ' << " B : " << hull.B <<'\n';
      os << "Points in hulls : " << '\n';
      int sz = (int)hull.chVec.size();
      for (int i = 0; i < sz; ++i) {
         os << hull.chVec[i].x << ' ' << hull.chVec[i].y << '\n';
      }
      os << "Line segments of hulls : " << '\n';
      for (int i = 0; i < sz; ++i) {
         os << hull.chVec[i].x << ' ' << hull.chVec[i].y << ' ' <<
            hull.chVec[(i+1) % sz].x << ' ' << hull.chVec[(i+1) % sz].y << '\n';
      }
      return os;
   }
};

// convexHull, smallest polygon such that all points lie inside or on it
// no triplet exist which are collinear, clockwise order of points in res
CH grahamScan (vector <pt> &a) { // in O(NlogN), N is the number of points given
   CH hull;
   sort(a.begin(), a.end()); // sort based on left-most-down
   if ((int)a.size() <= 2) { // Hull of points less than two
      hull.chVec = a;
      return hull;
   }
   vector <pt> up, down;
   pt A = a.front(), B = a.back(); // A is left-most-down and B is right-most-up
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
   // insert the up part of the hull in increasing order of their x
   for (int i = 0; i < (int)up.size(); ++i) {
      hull.chVec.push_back(up[i]);
   }
   // insert the down part of hull in decreasing order of their x
   // to maintain clockwise order points in hull
   for (int i = (int)down.size()-2; i > 0; --i) { // skip A (first el)and B (lst el)
      hull.chVec.push_back(down[i]);
   }
   return hull;
}

bool liesInsideConvexPolygon(pt qry, const CH& hull, bool strictInside) { // log2(N), N is the size of convex polygon
   pt A = hull.chVec.front(); // left-down most
   // qry.x should be in the range [A.x, infi)
   if (qry.x < A.x) {
      return false;
   }
   pt Ad = hull.chVec[1]; // second left-down most
   pt B = hull.chVec.back(); //  last point clockwise
   // lies in the first or last zone
   if (qry.aboveLine(A, Ad) || qry.belowLine(A, B)) {
      return false;
   }
   // Lies on the first or last line
   if (qry.onLine(A, Ad) || qry.onLine(A, B)) {
      return (strictInside ? false : true);
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
   // Lies on the line CD
   if (qry.onLine(C, D)) {
      return (strictInside ? false : true);
   }
   // Lies inside the triangle (A, C, D)
   if (qry.pointInTriangle(A, C, D)) {
      return true;
   }
   return false;
}

bool liesOnHull(pt qry, const CH& hull) { // log2(N), N is the size of convex polygon
   pt A = hull.chVec.front(); // left-down most
   // before A
   if (qry.x < A.x) {
      return false;
   }
   pt Ad = hull.chVec[1]; // second left-down most
   pt B = hull.chVec.back(); //  last point clockwise
   // Lies in the first or last zone
   if (qry.aboveLine(A, Ad) || qry.belowLine(A, B)) {
      return false;
   }
   // Lies on the first or last line
   if (qry.onLine(A, Ad) || qry.onLine(A, B)) {
      return true;
   }
   // figure out the triangular region, where qry can lie in
   int L = 1, H = (int)hull.chVec.size()-2;
   while (L <= H) {
      int g = (L+H)/2;
      if (qry.belowLine(A, hull.chVec[g])) L=g+1;
      else H=g-1;
   }
   pt C = hull.chVec[H], D = hull.chVec[H+1];
   // Lies on the line CD
   if (qry.onLine(C, D)) {
      return true;
   }
   return false;
}

// slower version of liesInsideConvexPolygon which was O(logN), and this is O(N)
bool onAndInsidePolygon(pt qry, const CH &hull, bool strictInside) { // O(N), N is the size of polygon
   pt A = hull.chVec.front(); // pivot // v[0]
   double hullArea = 0.0, pointHullArea = 0.0;
   // sum of area of all triangles (A, vi, vi+1), gives area of polygon
   int sz = (int)hull.chVec.size();
   for (int i = 1; i < sz-1; ++i) {
      hullArea += fabs(A.cross(hull.chVec[i], hull.chVec[i+1]));
   }
   // area coming out from qry
   for (int i = 0; i < sz; ++i) {
      pointHullArea += fabs(qry.cross(hull.chVec[i], hull.chVec[(i+1) % sz]));
   }
   if (strictInside) {
      // Should'nt lie on the polygon itself
      for (int i = 0; i < sz; ++i) {
         if (qry.onLine(hull.chVec[i], hull.chVec[(i+1) % sz])) {
            return false;
         }
      }
   }
   // both areas should be same for the point to be inside or on
   return isZero(hullArea - pointHullArea);
}

vector <CH> layers; // concentric layers from inside to outside
set <pt> pts; // set of original N given points
int n, q;

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
   }
   // find layers of convex hulls
   while ((int)pts.size() > 2) { // O(N * N log2N), should be quite less than that
      vector <pt> lft(pts.begin(), pts.end());
      CH hull = grahamScan(lft);
      if ((int)hull.chVec.size() > 2) {
         layers.push_back(hull);
         // remove the points which are already taken on convex hull or which lies on it
         vector <pt> rem;
         for (pt P : pts) {
            if (liesOnHull(P, layers.back())) {
               rem.push_back(P);
            }
         }
         for (pt P : rem) pts.erase(P);
      }
      else {
         break;
      }
   }
   int mxLayer = (int)layers.size();
   // showLayers(mxLayer);
   // for each query
   // do binary search to find the cocentric convex hulls it is in inside
   while (q--) { // O(Q * log2N * log2N)
      int X, Y;
      cin >> X >> Y;
      pt qry(X, Y);
      int L = 0, H = mxLayer-1;
      while (L <= H) {
         int g = (L+H)/2;
         if (liesInsideConvexPolygon(qry, layers[g], true))
            L = g+1;
         else H = g-1;
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
