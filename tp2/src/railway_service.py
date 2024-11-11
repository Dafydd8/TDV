import json
import networkx as nx
from math import ceil
import matplotlib.pyplot as plt

def load_instance(filename):
    '''Cargar una instancia de un archivo JSON'''
    with open(filename) as json_file:
        data = json.load(json_file)
    return data

def create_graph(data):
    '''Crea el grafo del problema de circulación a partir de la información de la instancia.
        Devuelve el grafo y un diccionario con los tiempos de salida y llegada de cada estación ordenados de menor a mayor.
    '''
    G = nx.DiGraph()
    services = data["services"] # Diccionario con la información de los servicios
    rs_capacity = data["rs_info"]["capacity"] # Capacidad de los RS
    max_rs = data["rs_info"]["max_rs"] # Máximo de RS que se pueden usar
    a = data["stations"][0] # Estación 'a'
    b = data["stations"][1] # Estación 'b'

    nodos_estacion = {a: [], b: []} # Diccionario con los tiempos de salida y llegada de cada estación

    for service in services:
        stops = services[service]["stops"] 
        salida = stops[0]
        salida_str = salida["station"]+"_"+str(salida["time"]) # Identificador del nodo de salida
        llegada = stops[1]
        llegada_id = llegada["station"]+"_"+str(llegada["time"]) # Identificador del nodo de llegada
        needed_rs = ceil(services[service]["demand"][0]/rs_capacity) # RS necesarios para el servicio
        nodos_estacion[salida["station"]].append(salida["time"]) # Agregar el tiempo de salida a la lista de tiempos de la estación
        nodos_estacion[llegada["station"]].append(llegada["time"]) # Agregar el tiempo de llegada a la lista de tiempos de la estación

        G.add_node(salida_str, demand = 0) # Crear nodo de salida
        G.add_node(llegada_id, demand = 0) # Crear nodo de llegada
        G.add_edge(salida_str, llegada_id, weight = 0, lower_bound = needed_rs, upper_bound = max_rs) # Crear arista entre la salida y la llegada

    nodos_estacion[a].sort()
    nodos_estacion[b].sort()

    # Crear aristas entre los nodos de la misma estación
    for i in range(len(nodos_estacion[a])-1):
        G.add_edge(a+"_"+str(nodos_estacion[a][i]), a+"_"+str(nodos_estacion[a][i+1]), weight = 0, lower_bound = 0, upper_bound = 1e9)
        G.add_edge(b+"_"+str(nodos_estacion[b][i]), b+"_"+str(nodos_estacion[b][i+1]), weight = 0, lower_bound = 0, upper_bound = 1e9)
    
    # Crear aristas entre el último y el primer nodo de cada estación
    G.add_edge(a+"_"+str(nodos_estacion[a][-1]), a+"_"+str(nodos_estacion[a][0]), weight = 1, lower_bound = 0, upper_bound = 1e9)
    G.add_edge(b+"_"+str(nodos_estacion[b][-1]), b+"_"+str(nodos_estacion[b][0]), weight = 1, lower_bound = 0, upper_bound = 1e9)

    return G, nodos_estacion

def transform_graph(G):
    '''Transforma el grafo de circulación en un grafo de flujo de costo mínimo'''
    H = nx.DiGraph()
    for u, v, data in G.edges(data=True):
        l_bound = data["lower_bound"]
        u_bound = data["upper_bound"]
        weight = data["weight"]
        # Añadir los mismos nodos de G a H
        H.add_node(u, demand = 0)
        H.add_node(v, demand = 0)
        # Añadir aristas con nueva capacidad
        H.add_edge(u, v, weight = weight, capacity = u_bound - l_bound) # 

    #Calcular nuevos imbalances para cada nodo
    for u, v, data in G.edges(data=True):
        l_bound = data["lower_bound"]
        H.nodes[u]["demand"] += l_bound
        H.nodes[v]["demand"] -= l_bound

    return H

def solve_circulacion(G):
    '''Resolver el problema de circulación reduciéndolo a un problema de flujo de costo mínimo'''
    H = transform_graph(G)
    cost, circulacion = nx.network_simplex(H) # Resolver el problema de circulación con network_simplex
    for u in circulacion:
        for v in circulacion[u]:
            circulacion[u][v] = circulacion[u][v] + G[u][v]["lower_bound"] # Convertir la respuesta del problema de flujo de costo mínimo a la del problema de circulación
    return cost, circulacion

def show_graph(G, data, nodos_estacion):
    '''Mostrar un grafo G (de circulación o de flujo de costo mínimo) en dos columnas, con los nodos de la estación 'a' a la izquierda y los de la estación 'b' a la derecha'''

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
    nx.draw_networkx_nodes(G, pos, node_size=400, node_color="lightblue")
    nx.draw_networkx_labels(G, pos, font_size=7, font_weight="regular")
    nx.draw_networkx_edges(G, pos,connectionstyle='arc3,rad=0.2', arrowstyle='-|>')
    edge_labels = {}
    for u, v, data in G.edges(data=True):
        if ("lower_bound" in data) and ("upper_bound" in data): #Si es de circulación
            edge_labels[(u, v)] = f"l: {data['lower_bound']} - c: {data['upper_bound']}"
        elif ("capacity" in data): #Si es de flujo de costo mínimo
            edge_labels[(u, v)] = f"u: {data['capacity']}"
    nx.draw_networkx_edge_labels(G, pos, connectionstyle='arc3,rad=0.2', edge_labels=edge_labels, font_size=7, font_color="red")

    # Mostrar el gráfico
    plt.show()

def show_flow(G, flow, data, nodos_estacion):
    '''Mostrar el flujo flow en el grafo G organizado en dos columnas, con los nodos de la estación 'a' a la izquierda y los de la estación 'b' a la derecha'''
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