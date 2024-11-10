import networkx as nx
import matplotlib.pyplot as plt

def flujo_max(G, s, t):
    flow_value, _ = nx.maximum_flow(G, s, t)
    return flow_value

G = nx.DiGraph()
G.add_nodes_from(range(8))
aristas = [(0, 1), (0, 2), (0, 3), (1, 4), (2, 5), (3, 6), (4, 7),(5, 7), (6, 7)]
for (i, j) in aristas:
    G.add_edge(i, j, capacity=1)
#pos = nx.spring_layout(G)
#nx.draw(G, pos, with_labels=True, node_color='lightblue')
#plt.show()
print(flujo_max(G, 0, 7))

G_alt = G.copy() #NO LO TERMINE... NO APORTABA NADA NUEVO
for nodo in list(G.nodes):
    if nodo != 0 and nodo != 7:

        G_alt.add_node(nodo)
        G_alt.add_edge(0, nodo, capacity=1)
    G_alt.add_edge(7, nodo, capacity=1)