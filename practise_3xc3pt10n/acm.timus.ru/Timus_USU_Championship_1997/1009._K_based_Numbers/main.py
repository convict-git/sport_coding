import sys
sys.setrecursionlimit(1500)
N = int(input())
K = int(input())
Mod = int(input())


def mul(A, B, m, n, p):  # mxn nxp
    M = [[0 for j in range(p)] for i in range(m)]
    for r in range(m):
        for c in range(p):
            for k in range(n):
                M[r][c] = (M[r][c] + A[r][k]*B[k][c]) % Mod
    return M

Id = [[1, 0], [0, 1]]
M = [[K, K], [1, 0]]
f = [[((K-1) * (K-1)) % Mod], [K-1]]

m = int(N-2)
res = Id
while (m != 0):
    if (m % 2 == 1):
        res = mul(res, M, 2, 2, 2)
    M = mul(M, M, 2, 2, 2)
    m = m//2

res = mul(res, f, 2, 2, 1)
print(res[0][0] + res[1][0])
