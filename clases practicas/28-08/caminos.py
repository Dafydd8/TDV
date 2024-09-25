def crear_matriz(m,n):
    aux = []
    for i in range(m):
        aux2 = []
        for j in range(n):
            aux2.append(-1)
        aux.append(aux2)
    return aux

def caminos(a, i, j):
    if i >= len(a) or j >= len(a[0]) or a[i][j] == 1:
        return 0
    if i == len(a) - 1 and j == len(a[0]) - 1:
        return 1
    n1 = caminos(a, i + 1, j)
    n2 = caminos(a, i, j + 1)
    return n1 + n2

def caminos_PD(a, i, j, aux):
    if i >= len(a) or j >= len(a[0]) or a[i][j] == 1:
        return 0
    if i == len(a) - 1 and j == len(a[0]) - 1:
        return 1
    if len(aux) == 0:
        aux = crear_matriz(len(a), len(a[0]))
    if aux[i][j] != -1:
        return aux[i][j]
    n1 = caminos_PD(a, i + 1, j, aux)
    n2 = caminos_PD(a, i, j + 1, aux)
    aux[i][j] = n1 + n2  
    return n1 + n2

a = [[0, 1,1], [0, 1,1], [0, 0, 0]]
aux = []

print(caminos_PD(a, 0, 0, aux))  # 2
