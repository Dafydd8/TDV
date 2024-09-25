def grafo_completo(n: int) -> list[list[int]]:
    """Dado un número natural n devolver la matriz de adyacencia de un grafo completo con n vértices.
    Ayuda: Asumir que los nodos son {0,1,..,n-1}.
    Args:
        n (int): Cantidad de vértices del grafo.

    Returns:
        List[List[int]]: La matriz de adyacencia de un grafo completo.
    """
    rv = []
    for i in range(n):
        linea = []
        for j in range(n):
            if j != i:
                linea.append(1)
            else:
                linea.append(0)
        rv.append(linea)
    return rv
    


def grafo_bipartito_completo(n: int, m: int) -> list[list[int]]:
    """Dado dos números naturales n y m devolver la matriz de adyacencia de un grafo bipartito completo que tiene n vértices en una de
    sus particiones y m vértices en la otra.
    Asumir que los nodos de la primera particion son {0,1,..,n-1} y los de la segunda son {n,n+1,..,n+m-1}
    Args:
        n (int): Cantidad de vértices de la partición izquierda.
        m (int): Cantidad de vértices de la partición derecha.

    Returns:
        List[List[int]]: La matriz de adyacencia de un grafo bipartito completo
    """
    rv = []
    for i in range(n):
        linea = []
        for j in range(n+m):
            if j == i or j < n:
                linea.append(0)
            else:
                linea.append(1)
        rv.append(linea)
    for i in range(m):
        linea = []
        for j in range(n+m):
            if j >= n:
                linea.append(0)
            else:
                linea.append(1)
        rv.append(linea)
    return rv


def grafo_rueda(n: int) -> list[list[int]]:
    """Dado un natural n >= 4 devolver la matriz de adyacencia de un grado rueda de n vértices.
    Asumir que el nodo del centro es n-1 y los nodos del 0 hasta el n-2 forman en círculo en el orden 0-1-..-(n-2).
    Ayuda: https://es.wikipedia.org/wiki/Grafo_rueda
    Args:
        n (int): Cantidad de vértices del grafo.

    Returns:
        List[List[int]]: La matriz de adyacencia de un grafo rueda.
    """
    rv = []
    for i in range(n):
        linea = []
        for j in range(n):
            if i == 0:
                if j == 1 or j == n-1 or j == n-2:
                    linea.append(1)
                else:
                    linea.append(0)
            elif i == n-2:
                if j == 0 or j == n-3 or j == n-1:
                    linea.append(1)
                else:
                    linea.append(0)
            elif i == n-1:
                if i != j:
                    linea.append(1)
                else:
                    linea.append(0)
            else:
                if j == i + 1 or j == i - 1 or j == n-1:
                    linea.append(1)
                else:
                    linea.append(0)
        rv.append(linea)
    return rv


def grafo_rueda_lindo(n):
    rv = [[0 for _ in range(n)] for _ in range(n)]
    for i in range(n-1):
        rv[i][n-1] = 1
        rv[n-1][i] = 1
        rv[i][(i+1) % (n-1)] = 1
        rv[(i+1) % (n-1)][i] = 1
    return rv

def print_matriz(ls):
    for linea in ls:
        print(linea)

#print_matriz(grafo_bipartito_completo(2,2))