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

#include <bits/stdc++.h>
using namespace std;

/* Thanks to tourist */
/*{{{*/
template <typename T>
T inverse(T a, T m) {
   T u = 0, v = 1;
   while (a != 0) {
      T t = m / a;
      m -= t * a; swap(a, m);
      u -= t * v; swap(u, v);
   }
   assert(m == 1);
   return u;
}

template <typename T>
class Modular {
   public:
      using Type = typename decay<decltype(T::value)>::type;

      constexpr Modular() : value() {}
      template <typename U>
         Modular(const U& x) {
            value = normalize(x);
         }

      template <typename U>
         static Type normalize(const U& x) {
            Type v;
            if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
            else v = static_cast<Type>(x % mod());
            if (v < 0) v += mod();
            return v;
         }

      const Type& operator()() const { return value; }
      template <typename U>
         explicit operator U() const { return static_cast<U>(value); }
      constexpr static Type mod() { return T::value; }

      Modular& operator+=(const Modular& other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
      Modular& operator-=(const Modular& other) { if ((value -= other.value) < 0) value += mod(); return *this; }
      template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
      template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
      Modular& operator++() { return *this += 1; }
      Modular& operator--() { return *this -= 1; }
      Modular operator++(int) { Modular result(*this); *this += 1; return result; }
      Modular operator--(int) { Modular result(*this); *this -= 1; return result; }
      Modular operator-() const { return Modular(-value); }

      template <typename U = T>
         typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
            value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
            return *this;
         }
      template <typename U = T>
         typename enable_if<is_same<typename Modular<U>::Type, int64_t>::value, Modular>::type& operator*=(const Modular& rhs) {
            int64_t q = static_cast<int64_t>(static_cast<long double>(value) * rhs.value / mod());
            value = normalize(value * rhs.value - q * mod());
            return *this;
         }
      template <typename U = T>
         typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
            value = normalize(value * rhs.value);
            return *this;
         }

      Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }

      template <typename U>
         friend const Modular<U>& abs(const Modular<U>& v) { return v; }

      template <typename U>
         friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);

      template <typename U>
         friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);

      template <typename U>
         friend std::istream& operator>>(std::istream& stream, Modular<U>& number);

   private:
      Type value;
};

template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }

template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }

template <typename T> bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }

template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }

template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }

template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }

template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }

template<typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
   assert(b >= 0);
   Modular<T> x = a, res = 1;
   U p = b;
   while (p > 0) {
      if (p & 1) res *= x;
      x *= x;
      p >>= 1;
   }
   return res;
}

template <typename T>
bool IsZero(const Modular<T>& number) {
   return number() == 0;
}

template <typename T>
string to_string(const Modular<T>& number) {
   return to_string(number());
}

template <typename T>
std::ostream& operator<<(std::ostream& stream, const Modular<T>& number) {
   return stream << number();
}

template <typename T>
std::istream& operator>>(std::istream& stream, Modular<T>& number) {
   typename common_type<typename Modular<T>::Type, int64_t>::type x;
   stream >> x;
   number.value = Modular<T>::normalize(x);
   return stream;
}
/*}}}*/

// constexpr int md = 998244353;
constexpr int md = (int) 1e9 + 7;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;
void preproc() {
}

void solve() {
   const int maxdig = 12;
   int m;
   cin >> m;
   string s = to_string(m) + '0';
   while ((int)s.size() != maxdig) s = '0' + s;
   reverse(s.begin(), s.end());
   // input taking over

   vector <vector <vector <Mint>>> les;
   vector <vector <Mint>> eq;
   les.assign(maxdig, vector <vector <Mint>> (maxdig, vector <Mint> (10)));
   eq.assign(maxdig, vector <Mint> (maxdig));

   eq[0][0] = les[0][0][0] = Mint(1); // base case

   for (int pos = 1; pos < maxdig; ++pos) {
      int cur = s[pos] - '0', prv = s[pos - 1] - '0';
      for (int luck = 0; luck < maxdig; ++luck) {
         /*
            upd les
            les[pos][luck][{4,7}] = { les[pos-1][luck-1][all ends] }
            les[pos][luck][ends-{4,7}] = { les[pos-1][luck][all ends] }
            */
         for (int ends = 0; ends <= 9; ++ends) {
            for (int lstend = 0; lstend <= 9; ++lstend) {
               les[pos][luck][ends] += (ends == 4 || ends == 7 ?
                     (luck ? les[pos - 1][luck - 1][lstend] : 0)
                     : les[pos - 1][luck][lstend]);
            }
         }
         /*
            upd eq
            eq[pos][luck] = { les[pos-1][luck][all ends < last m's digit]
            + eq[pos - 1][luck] , if cur digit not in {4,7}}
            eq[pos][luck] = { les[pos-1][luck-1][all ends < last m's digit]
            + eq[pos-1][luck-1], if cur digit in {4,7} }
            */
         eq[pos][luck] = (cur == 4 || cur == 7 ?
               (luck ? eq[pos - 1][luck - 1] : 0)
               : eq[pos - 1][luck]);

         for (int ends = 0; ends < prv; ++ends) {
            eq[pos][luck] += (cur == 4 || cur == 7 ?
                  (luck ? les[pos - 1][luck - 1][ends] : 0)
                  : les[pos - 1][luck][ends]);
         }
      }
   }

   vector <Mint> dp(maxdig), pref(maxdig);
   for (int pos = 0; pos < maxdig; ++pos) {
      dp[pos] = eq[maxdig - 1][pos]; // no. of elements in [1, .. m] with pos
      if (pos == 0) {
         --dp[pos]; // remove 0 as range is [1, .., m]
      }
      if (pos)
         pref[pos] = pref[pos - 1] + dp[pos - 1];
   }

   auto C = [&] (const Mint& x, int k) -> Mint { // Choose function
      Mint ch(1);
      int den = 1;
      for (int ded = 0; ded < k; ++ded) {
         ch *= (x - Mint(ded));
         den *= ded + 1;
      }
      ch *= Mint(inverse(den,md));
      return ch;
   };

   // cnt [pos][sum][use] : no. of ways to selected 'use' numbers such that
   // sum of the lucky numbers IS 'sum' and you have used lucks inrange [0, pos]
   Mint res = 0;
   vector <vector <vector <Mint>>> cnt;
   cnt.assign(maxdig, vector <vector <Mint>> (maxdig, vector <Mint> (7)));
   for (int p = 0; p <= 6; ++p)  {
      cnt[0][0][p] = C(dp[0], p);
   }

   for (int pos = 1; pos < maxdig; ++pos) {
      for (int sum = 0; sum < maxdig; ++sum) {
         for (int use = 0; use <= 6; ++use) {
            for (int p = 0; p < maxdig; ++p) {
               if (sum - p * pos >= 0 && use - p >= 0) {
                  cnt[pos][sum][use] +=
                     cnt[pos - 1][sum - p * pos][use - p] * C(dp[pos], p);
               }
            }
         }
      }
      Mint cur(0);
      for (int sum = 0; sum < pos; ++sum) {
         cur += cnt[pos - 1][sum][6];
      }
      res += dp[pos] * cur * Mint(720);
   }
   cout << res << '\n';
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

