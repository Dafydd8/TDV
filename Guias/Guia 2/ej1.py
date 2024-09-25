import random

#a
def cant_nodos(clique):
    rv = 0
    for i in clique:
        if i == 1:
            rv += 1
    return rv

def agregable(nodo, aristas, clique):
    for i in range(len(clique)):
        if clique[i] == 1 and not(nodo in aristas[i]):
            return False
    return True

def clique_max(nodo, aristas, clique):
    if nodo == len(aristas):
        return clique
    
    sin = clique_max(nodo+1, aristas, clique[:] + [0])
    if agregable(nodo, aristas,clique):
        con = clique_max(nodo+1, aristas, clique[:] + [1])
        if cant_nodos(sin) > cant_nodos(con):
            return sin
        else:
            return con
    else:
        return sin

aristas = [[1,2], [0,2], [0,1,3], [2]]
clique = []
print(clique_max(0, aristas, clique))