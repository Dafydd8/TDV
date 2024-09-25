import random
from grafo import Grafo


def topo_sort(grafo: Grafo) -> list[any]:
    rv = []
    for i in range(grafo.tamanio()):
        for nodo in grafo.nodos:
            if grafo.in_degree(nodo) == 0:
                rv.append(nodo)
                grafo.eliminar_nodo2(nodo)
                break
    return rv 

def grafo_pasta() -> Grafo:
    grafo = Grafo()
    nodos = [
        "Pre-calentar horno", #0
        "Hornear el pan", #1
        "Servir el pan", #2
        "Comer", #3
        "Preparar la mesa", #4
        "Servir la bebida", #5
        "Servir la pasta", #6
        "Hervir el agua", #7
        "Tirar la pasta en el agua", #8
        "Preparar la salsa", #9
        "Colocar la salsa en la pasta", #10
    ]
    for nodo in nodos:
        grafo.agregar_nodo(nodo)
    for inicio, fin in [
        (nodos[0], nodos[1]),
        (nodos[1], nodos[2]),
        (nodos[2], nodos[3]),
        (nodos[4], nodos[2]),
        (nodos[4], nodos[5]),
        (nodos[5], nodos[3]),
        (nodos[4], nodos[6]),
        (nodos[10], nodos[3]),
        (nodos[7], nodos[8]),
        (nodos[8], nodos[6]),
        (nodos[9], nodos[10]),
        (nodos[6], nodos[10]),
    ]:
        grafo.agregar_arista(inicio, fin)

    return grafo


def checker(lista_topo_sort: list[any], grafo: Grafo) -> bool:
    for inicio, fin in grafo.aristas:
        indice_inicio = lista_topo_sort.index(inicio)
        indice_fin = lista_topo_sort.index(fin)
        if indice_inicio > indice_fin:
            return False

    return True


if __name__ == "__main__":
    grafo = grafo_pasta()
    lista_topo_sort = topo_sort(grafo)
    try:
        if checker(lista_topo_sort, grafo_pasta()):
            print("La solucion es correcta :D")
            print(lista_topo_sort)
        else:
            print("Algo esta mal :(")
            print(lista_topo_sort)
    except ValueError:
        print("No estan todos los nodos en la lista devuelta")