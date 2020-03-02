#include         <bits/stdc++.h>
#define x        first
#define y        second
using namespace std;
using pii = pair <int, int>;
int n, m;
int cx, cy;
set <pii> S;

void show() {
  for (int r = 0; r < n; ++r) {
    string st = "";
    for (int c = 0; c < m; ++c) {
      if (S.find(pii(r, c)) != S.end()) st += "\033[41m   \033[0m";
      else if (r == cx && c == cy) st += "\033[44m  \033[0m";
      else st += "\033[42m \033[0m";
    }
    cout << st << '\n';
  }
}


const int Mod = (int)1e9 + 7;
inline int add (int x, int y){ return (x + y) % Mod; }
inline int mul (int x, int y) { return 1ll*x*y % Mod; }
inline int pow (int x, int y) {
  int res = 1;
  while (y) {
    if (y & 1) res = mul(x, res);
    x = mul(x, x);
    y >>= 1;
  }
  return res;
}
inline int inv (int x) { return pow(x, Mod-2); }
inline int dv (int x, int y) { return mul(x, inv(y)); }

int main() {
  char c;
  cout << "Enter n and m: ";
  cin >> n >> m;
  cout << '\n';
  while (true) {
    cin >> c;
    system("clear");
    if (c == 's') {
      auto it = S.find(pii(cx, cy));
      if (it == S.end()) S.insert (pii(cx, cy));
      else S.erase(it);
    }
    else if (c == 'h') cy -= 1, cy = (cy + n)%n;
    else if (c == 'l') cy += 1, cy %= n;
    else if (c == 'j') cx += 1, cx %= m;
    else if (c == 'k') cx -= 1, cx = (cx + m)%m;
    show();
    cerr << cx << ' ' << cy << '\n';
    system("sleep 0.1");
  }

  return EXIT_SUCCESS;
}

