#include      <bits/stdc++.h>
using namespace std;
#define IOS       ios_base::sync_with_stdio(false); cin.tie (nullptr)
#define PREC      cout.precision (0); cout << fixed
#ifdef CONVICTION
#include "/home/convict/Dropbox/myfiles/sport_coding/cplib/snippets/debug.h"
#else
#define debug(x...)
#endif
//Don’t practice until you get it right. Practice until you can’t get it wrong

// geometry part
constexpr double eps = 1e-9;
inline bool isZero(double x) {
   return fabs(x) < eps;
}
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

struct CH {
   vector <pt> chVec; // point of convexHull
   pt A, B; // left-down and right-up
   int bidx; // index of B in chVec
};

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
      // cerr << up[i].x << ' ' << up[i].y << '\n';
   }
   // insert the down part of hull in decreasing order of their x
   // to maintain clockwise order points in hull
   for (int i = (int)down.size()-2; i > 0; --i) { // skip A (first el)and B (lst el)
      hull.chVec.push_back(down[i]);
   }
   return hull;
}

int n;

void preproc() {
}

void solve() {
   vector <pt> pts(n);
   for (int i = 0; i < n; ++i) {
      cin >> pts[i].x >> pts[i].y;
   }
   sort(pts.begin(), pts.end());
   pts.erase(unique(pts.begin(), pts.end()), pts.end());

   CH hull = grahamScan(pts);
   reverse(hull.chVec.begin(), hull.chVec.end());
   cout << hull.chVec.size() << '\n';
   for (pt p : hull.chVec) {
      cout << p.x << ' ' << p.y << '\n';
   }
}

signed main() {
  IOS; PREC;
  preproc();

  int tc = 1;
  // cin >> tc;
  for (int Tt = 1; Tt <= tc; ++Tt) {
    // cout << "Case #" << Tt << ": ";
    while (cin >> n, n) solve();
  }
  return EXIT_SUCCESS;
}
