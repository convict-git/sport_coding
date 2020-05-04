const int N = 1 << 10;
string S(N, ' '), T(N, ' ');

for (int i = 0; i < N; i++)
    S[i] = 'A' + __builtin_popcount(i) % 2;
for (int i = 0; i < N; i++)
    T[i] = 'B' - __builtin_popcount(i) % 2;
