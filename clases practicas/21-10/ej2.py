import networkx as nx
import matplotlib.pyplot as plt

def dis_min_a_todos(G):
    for i in list(G.nodes):
        for j in list(G.nodes):
            if i != j:
                print(f"Distancia minima de {i} a {j}: {nx.shortest_path_length(G, i, j, weight='weight')}")

def camino_max_arbol(T):
    max_path_length = 0
    for nodo in list(T.nodes):
        for nodo2 in list(T.nodes):
            if nodo != nodo2:
                path_length = nx.shortest_path_length(T, nodo, nodo2, weight='weight')
                if path_length > max_path_length:
                    rv = nx.shortest_path(T, nodo, nodo2, weight='weight')
                    max_path_length = path_length
    return rv
        
G = nx.Graph()
G.add_nodes_from(range(5))
for i in range(4):
    G.add_edge(i, i+1, weight=1)
#dis_min_a_todos(G)

T = nx.Graph()
T.add_nodes_from(range(7))
aristas = [(0, 1), (1, 4), (1, 2), (3, 2), (5, 2), (5,6)]
for (i, j) in aristas:
    T.add_edge(i, j, weight=1)
nx.draw(T, with_labels=True, node_color='lightblue')
print(camino_max_arbol(T))
plt.show()

