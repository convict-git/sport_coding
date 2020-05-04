#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

/* mult function multiples two int a, b and gives the result modulo MOD */
inline int mult (int a, int b) {
  return int (1ll*(a + MOD)*(b + MOD) % MOD);
}

/* add function adds two int a, b and gives the result modulo MOD */
inline int add (int a, int b) {
  return int ((1ll*MOD + a + b) % MOD);
}

int main() {
  int t;
  cin >> t;
  // for all test cases
  while (t--) {
    int n, m;
    int sig_a = 0, sig_b = 0; /* sig_a stores sum for A, and sig_b for B */
    cin >> n >> m;

    /* Take input for array A */
    for (int u, i = 0; i < n; ++i) {
      cin >> u;
      sig_a = add(sig_a, u); /* We use our add function to add */
    }

    /* Take input for array B */
    for (int v, i = 0; i < m; ++i) {
      cin >> v;
      sig_b = add(sig_b, v); /* We use our add function to add */
    }

    /* Answer all queries */
    int q;
    cin >> q;
    while (q--) {
      int qtype;
      cin >> qtype;

      if (qtype == 1) { // Type 1 query, i.e. update A
        int l, r, x;
        cin >> l >> r >> x;
        sig_a = add(sig_a, mult(r - l + 1, x));
      }

      else if (qtype == 2) { // Type 2 query, i.e. update B
        int l, r, x;
        cin >> l >> r >> x;
        sig_b = add(sig_b, mult(r - l + 1, x));
      }

      else { // Type 3 query, print score (A, B)
        cout << mult(sig_a, sig_b) << "\n";
      }
    }
  }
  return 0;
}



