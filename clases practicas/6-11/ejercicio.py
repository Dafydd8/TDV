import time
from input import *

INF = float("inf")
UNDEF = -1


class Solver:
    def __init__(self, G: list[list[float]]):
        self.G = G
        self.solucion = []

    def solve(self) -> tuple[list[int], float]:
        pass


class SolverFuerzaBruta(Solver):
    def solve(self):
        visitados = [0] * len(self.G)
        visitados[0] = 1
        mejor_solucion, resultado = self.tsp_fuerza_bruta(0, visitados)
        return mejor_solucion, resultado

    def tsp_fuerza_bruta(self, u, visitado):
        if sum(visitado) == len(self.G):
            return [0], self.G[u][0]
        min_cost = INF
        mejor_sufijo = []
        for v in range(len(self.G)):
            if not visitado[v]:
                visitado[v] = True
                sufijo, costo = self.tsp_fuerza_bruta(v, visitado)
                if self.G[u][v] + costo < min_cost:
                    min_cost = self.G[u][v] + costo
                    mejor_sufijo = [v] + sufijo
                visitado[v] = False
        return mejor_sufijo, min_cost


class SolverDP(Solver):
    def solve(self):
        n = len(self.G)
        self.memo = [[UNDEF] * (1 << n) for _ in range(n)]
        self.next_node = [[UNDEF] * (1 << n) for _ in range(n)]
        resultado = self.tsp_dp(0, 1)
        self.reconstruir_solucion()
        return self.solucion, resultado

    def tsp_dp(self, u, mask):
        if mask == (1 << len(self.G)) - 1:
            self.next_node[u][mask] = 0
            return self.G[u][0]

        if self.memo[u][mask] != UNDEF:
            return self.memo[u][mask]
        min_cost = INF
        for v in range(len(self.G)):
            if (mask & (1 << v)) == 0:
                new_mask = mask | (1 << v)
                costo = self.G[u][v] + self.tsp_dp(v, new_mask)
                if costo < min_cost:
                    min_cost = costo
                    self.next_node[u][mask] = v

        self.memo[u][mask] = min_cost
        return min_cost

    def reconstruir_solucion(self):
        mask = 1
        nodo = 0
        self.solucion = [nodo]
        while True:
            v = self.next_node[nodo][mask]
            if v == 0:
                break
            self.solucion.append(v)
            mask = mask | (1 << v)
            nodo = v


class SolverVecinoMasCercano(Solver):
    def solve(self):
        visitado = [False] * len(self.G)
        u = 0
        visitado[u] = True
        self.solucion.append(u)
        cost = 0
        for _ in range(len(self.G) - 1):
            min_v, min_cost = self.elegir_arista_mas_cercana(u, visitado)
            cost += min_cost
            visitado[min_v] = True
            u = min_v
            self.solucion.append(u)
        return self.solucion, cost + self.G[u][0]

    def elegir_arista_mas_cercana(self, u, visitado):
        # Arreglar el comportamiento de la funcion
        min_v = -1
        for v in range(len(self.G[u])):
            if not visitado[v] and (min_v == -1 or self.G[u][v] < self.G[u][min_v]):
                min_v = v
        return min_v, self.G[u][min_v]


class SolverInsercion(Solver):

    def __init__(self, G: list[list[float]], mas_cercano: bool = True):
        super().__init__(G)
        self.mas_cercano = mas_cercano

    def elegir_nodo(self, visitado):
        # Arreglar el comportamiento de la funcion
        w = -1
        rta_v = -1
        if self.mas_cercano:
            for v in range(len(self.G)):
                if visitado[v]:
                    for u in range(len(self.G)):
                        if not visitado[u] and (w == -1 or self.G[u][v] < self.G[u][w]):
                            w = u
                            rta_v = v
        else:
            for v in range(len(self.G)):
                if visitado[v]:
                    for u in range(len(self.G)):
                        if not visitado[u] and (w == -1 or self.G[u][v] > self.G[u][w]):
                            w = u
                            rta_v = v
        return w

    def insertar_nodo(self, v):
        # Arreglar el comportamiento de la funcion
        min_u = self.solucion[0]
        min_w = self.solucion[-1]
        min_cost = self.G[min_u][v] + self.G[v][min_w] - self.G[min_u][min_w]

        for i in range(len(self.G[v])-1):
            u = self.solucion[i]
            w = self.solucion[i+1]
            costo = self.G[u][v] + self.G[v][w] - self.G[u][w]
            if costo < min_cost:
                min_cost = costo
                min_u = u
                min_w = w


        return min_u, min_w
    
    def solve(self):
        visitado = [False] * len(self.G)

        visitado[0] = visitado[1] = visitado[2] = True
        self.solucion.extend([0, 1, 2])
        cost = self.G[0][1] + self.G[1][2] + self.G[2][0]

        while len(self.solucion) < len(self.G):
            min_v = self.elegir_nodo(visitado)

            z, w = self.insertar_nodo(min_v)
            cost += self.G[z][min_v] + self.G[min_v][w] - self.G[z][w]

            visitado[min_v] = True

            if w == 0:
                self.solucion.append(min_v)
            else:
                self.solucion.insert(self.solucion.index(w), min_v)

        return self.solucion, cost


Methods = [
    "Fuerza Bruta",
    "DP",
    "Vecino Mas Cercano",
    "Insercion Vecino Mas Cercano",
    "Insercion Vecino Mas Lejano",
]


def solve(puntos: list[Point], method):
    G = transformar_en_grafo(puntos)
    start = time.time()
    if method == 0:
        solver = SolverFuerzaBruta(G)
    elif method == 1:
        solver = SolverDP(G)
    elif method == 2:
        solver = SolverVecinoMasCercano(G)
    elif method == 3:
        solver = SolverInsercion(G)
    elif method == 4:
        solver = SolverInsercion(G, False)
    solucion, result = solver.solve()
    end = time.time()
    print(f"{result}, con tiempo: {end - start}")
    graficar(puntos, solucion, result)


if __name__ == "__main__":
    ingreso = """Ingresar cantidad de puntos y metodo a utilizar:
    1.Fuerza bruta
    2.DP
    3.Vecino mas cercano
    4.Insercion vecino mas cercano
    5.Insercion vecino mas lejano
    """
    print(ingreso)
    n, metodo = map(int, input().split(" "))
    metodo -= 1
    print(f"Resolviendo TSP con {Methods[metodo]}")
    solve(generar_puntos_random(n), metodo)
