N = int(input())
T = [[] for u in range(N)]
R = [0 for u in range(N)]

for u in range(N):
    tmp = [int(x) for x in input().split()]
    R[u] = tmp[0]
    for i in range(1, len(tmp) - 1):
        v = tmp[i] - 1
        T[u].append(v)
        T[v].append(u)

root, vel = [int(x) for x in input().split()]
root -= 1

if vel == 0:
    for u in range(N):
        print('0/1')
    exit()

vis = [0 for u in range(N)]
depth = [0 for u in range(N)]
ome = [[0,1] for u in range(N)]

def gcd(x, y):
    if (y == 0):
        return x
    return gcd(y, x % y)

def dfs (u, d):
    vis[u] = 1
    depth[u] = d

    for v in T[u]:
        if vis[v] == 0:
            num = ome[u][0] * R[u]
            den = ome[u][1] * R[v]
            rem = gcd(num, den)
            num //= rem
            den //= rem

            ome[v] = [num, den]
            dfs(v, d + 1)

ome[root] = [abs(vel), 1]
dfs(root, 0)

for u in range(N):
    if ((depth[u] % 2 == 1 and vel > 0) or (depth[u] % 2 == 0 and vel < 0)):
        ome[u][0] *= -1
    print(str(ome[u][0]) + '/' + str(ome[u][1]))
