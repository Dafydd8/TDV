from numpy import average

def var(lista):
    suma = 0
    promedio = average(lista)
    for i in range(len(lista)):
        suma += (lista[i]-promedio)**2
    return suma/(len(lista)-1)

def grafo_varianzas(lista, p):
    if len(lista) == 0:
        return []
    rv = []
    origenes = {0}
    for desde in range(len(lista)):
        aristas_desde = [] 
        if desde in origenes:
            for hasta in range(desde+p, len(lista)+1):
                origenes.add(hasta)
                aristas_desde.append((hasta, float(var(lista[desde:hasta]))))
        rv.append(aristas_desde)
    rv.append([])
    return rv

def dijkstra(grafo, origen):
    distancias = [float('inf')]*len(grafo)
    distancias[origen] = 0
    visitados = set()
    a = 0
    while a < len(grafo):
        a+=1
        minimo = float('inf')
        nodo = None
        for i in range(len(grafo)):
            if i not in visitados and distancias[i] < minimo:
                minimo = distancias[i]
                nodo = i
        visitados.add(nodo)
        if (nodo != None):
            for arista in grafo[nodo]:
                if distancias[arista[0]] > distancias[nodo] + arista[1]:
                    distancias[arista[0]] = distancias[nodo] + arista[1]
    return distancias

lista = [5,3,2,4,1]


print(dijkstra(grafo_varianzas(lista, 2), 0)) #[0, inf, 2.0, 2.333333333333333, 1.6666666666666667, 2.5]