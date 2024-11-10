import networkx as nx
import matplotlib.pyplot as plt

def asignacion_feriados(k, n, c, d_s, s_s):
    G = nx.DiGraph()
    G.add_nodes_from(range(n+1))
    for i in range(1,n+1):
        G.add_edge(0, i, capacity=c)
    G.add_nodes_from(range(n+1, n+1+k))


