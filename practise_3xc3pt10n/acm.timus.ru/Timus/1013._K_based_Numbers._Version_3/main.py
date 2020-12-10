N = int(input())
K = int(input())
M = int(input())

mat = [ K-1, 1, K-1, 0 ]
res = [1, 0, 0, 1]
tmp = [0 for i in range(4)]

y = N-1
while (y > 0):
    if (y % 2 == 1):
        tmp[0] = res[0] * mat[0] + res[1] * mat[2]
        tmp[1] = res[0] * mat[1] + res[1] * mat[3]
        tmp[2] = res[2] * mat[0] + res[3] * mat[2]
        tmp[3] = res[2] * mat[1] + res[3] * mat[3]

        for i in range(4):
            res[i] = tmp[i] % M

    tmp[0] = mat[0] * mat[0] + mat[1] * mat[2]
    tmp[1] = mat[0] * mat[1] + mat[1] * mat[3]
    tmp[2] = mat[2] * mat[0] + mat[3] * mat[2]
    tmp[3] = mat[2] * mat[1] + mat[3] * mat[3]
    for i in range(4):
       mat[i] = tmp[i] % M

    y = y / 2

final = (K-1) * (res[0] + res[1]) % M
print(final)

