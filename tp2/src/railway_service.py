import json
import networkx as nx
from math import ceil
import matplotlib.pyplot as plt

def load_instance(filename):
    with open(filename) as json_file:
        data = json.load(json_file)
    return data

def create_graph(data):
    G = nx.DiGraph()
    services = data["services"]
    rs_capacity = data["rs_info"]["capacity"]
    max_rs = data["rs_info"]["max_rs"]
    a = data["stations"][0]
    b = data["stations"][1]

    nodos_estacion = {a: [], b: []}

    for service in services:
        stops = services[service]["stops"]
        salida = stops[0]
        salida_str = salida["station"]+"_"+str(salida["time"])
        llegada = stops[1]
        llegada_id = llegada["station"]+"_"+str(llegada["time"])
        needed_rs = ceil(services[service]["demand"][0]/rs_capacity)
        nodos_estacion[salida["station"]].append(salida["time"])
        nodos_estacion[llegada["station"]].append(llegada["time"])

        G.add_node(salida_str, demand = 0)
        G.add_node(llegada_id, demand = 0)
        G.add_edge(salida_str, llegada_id, weight = 0, lower_bound = needed_rs, upper_bound = max_rs)

    nodos_estacion[a].sort()
    nodos_estacion[b].sort()

    for i in range(len(nodos_estacion[a])-1):
        G.add_edge(a+"_"+str(nodos_estacion[a][i]), a+"_"+str(nodos_estacion[a][i+1]), weight = 0, lower_bound = 0, upper_bound = 1e9)
        G.add_edge(b+"_"+str(nodos_estacion[b][i]), b+"_"+str(nodos_estacion[b][i+1]), weight = 0, lower_bound = 0, upper_bound = 1e9)
    
    G.add_edge(a+"_"+str(nodos_estacion[a][-1]), a+"_"+str(nodos_estacion[a][0]), weight = 1, lower_bound = 0, upper_bound = 1e9)
    G.add_edge(b+"_"+str(nodos_estacion[b][-1]), b+"_"+str(nodos_estacion[b][0]), weight = 1, lower_bound = 0, upper_bound = 1e9)

    return G, nodos_estacion

def transform_graph(G):
    H = nx.DiGraph()
    for u, v, data in G.edges(data=True):
        l_bound = data["lower_bound"]
        u_bound = data["upper_bound"]
        weight = data["weight"]
        H.add_node(u, demand = 0)
        H.add_node(v, demand = 0)
        H.add_edge(u, v, weight = weight, capacity = u_bound - l_bound)

    for u, v, data in G.edges(data=True):
        l_bound = data["lower_bound"]
        H.nodes[u]["demand"] += l_bound
        H.nodes[v]["demand"] -= l_bound

    for node in H.nodes():
        print(node, H.nodes[node]["demand"])
    return H

def solve_circulacion(G):
    H = transform_graph(G)
    # Resolver el problema de circulación con network_simplex
    cost, circulacion = nx.network_simplex(H)
    for u in circulacion:
        for v in circulacion[u]:
            circulacion[u][v] = circulacion[u][v] + G[u][v]["lower_bound"]
    return cost, circulacion

def show_graph(G, data, nodos_estacion):
    # Crear un layout manual para organizar los nodos en dos columnas
    pos = {}

    # Posicionar nodos de la estación 'a' (columna izquierda)
    for i, time in enumerate(nodos_estacion[data["stations"][0]]):
        node_id = data["stations"][0] + "_" + str(time)
        pos[node_id] = (0, -i)

    # Posicionar nodos de la estación 'b' (columna derecha)
    for i, time in enumerate(nodos_estacion[data["stations"][1]]):
        node_id = data["stations"][1] + "_" + str(time)
        pos[node_id] = (2, -i)  # '2' para separar las columnas

    # Dibujar los nodos y las aristas
    #nx.draw(G, pos, with_labels=True, node_size=700, node_color="lightblue", font_size=10, font_weight="bold", arrows=True)
    nx.draw_networkx_nodes(G, pos, node_size=400, node_color="lightblue")
    nx.draw_networkx_labels(G, pos, font_size=7, font_weight="regular")
    nx.draw_networkx_edges(G, pos,connectionstyle='arc3,rad=0.2', arrowstyle='-|>')
    edge_labels = {(u, v): f"{data['lower_bound']}-{data['upper_bound']}" for u, v, data in G.edges(data=True)}
    nx.draw_networkx_edge_labels(G, pos, connectionstyle='arc3,rad=0.2', edge_labels=edge_labels, font_size=7, font_color="red")
    

    # Crear y dibujar las etiquetas de las aristas con cotas

    # Mostrar el gráfico
    plt.show()

def show_flow(G, flow, data, nodos_estacion):
    # Crear un layout manual para organizar los nodos en dos columnas
    pos = {}

    # Posicionar nodos de la estación 'a' (columna izquierda)
    for i, time in enumerate(nodos_estacion[data["stations"][0]]):
        node_id = data["stations"][0] + "_" + str(time)
        pos[node_id] = (0, -i)

    # Posicionar nodos de la estación 'b' (columna derecha)
    for i, time in enumerate(nodos_estacion[data["stations"][1]]):
        node_id = data["stations"][1] + "_" + str(time)
        pos[node_id] = (2, -i)  # '2' para separar las columnas

    # Dibujar el grafo original
    nx.draw_networkx_nodes(G, pos, node_size=400, node_color="lightblue")
    nx.draw_networkx_labels(G, pos, font_size=7, font_weight="regular")
    nx.draw_networkx_edges(G, pos, connectionstyle='arc3,rad=0.2', arrowstyle='-|>')
    
    # Crear etiquetas para mostrar el flujo en cada arista
    edge_labels = {}
    for u, v in G.edges():
        flujo = flow.get(u, {}).get(v, 0)
        edge_labels[(u, v)] = f"Flujo: {flujo}"

    # Dibujar etiquetas del flujo
    nx.draw_networkx_edge_labels(G, pos, connectionstyle='arc3,rad=0.2', edge_labels=edge_labels, font_color="red")

    # Mostrar el gráfico
    plt.show()