import networkx as nx
import matplotlib.pyplot as plt

def completo(n):
    G = nx.Graph()
    G.add_nodes_from(range(n))
    aristas = []
    for i in range(n):
        for j in range(i+1, n):
            aristas.append((i, j))
    G.add_edges_from(aristas)
    return G

def bipartito(n,m):
    G = nx.Graph()
    G.add_nodes_from(range(n+m))
    aristas = []
    for i in range(n):
        for j in range(n, n+m):
            aristas.append((i, j))
    G.add_edges_from(aristas)
    return G

def digraph_ciclico(n):
    G = nx.DiGraph()
    G.add_nodes_from(range(n))
    aristas = []
    for i in range(n):
        aristas.append((i, (i+1)%n))
    G.add_edges_from(aristas)
    return G

# Dibujar el grafo bipartito
G = bipartito(2,3)
top_nodes = set(range(2))  # Primer conjunto de nodos
bottom_nodes = set(range(2, 5))  # Segundo conjunto de nodos
pos = nx.bipartite_layout(G, top_nodes)
#nx.draw(G, pos, with_labels=True, node_color=['lightblue' if node in top_nodes else 'lightgreen' for node in G.nodes()])

# Dibujar el digrafo ciclico
G = digraph_ciclico(5)
pos = nx.circular_layout(G)
nx.draw(G,pos, with_labels=True, node_color='lightblue')

plt.show()



