from railway_service import *
import os

############################################################
# CREAR Y MOSTRAR EL GRAFO COMO SE PROPONE EN EL ENUNCIADO #
############################################################
file_name = os.path.join(os.path.dirname(__file__), '../instances/toy_instance.json')
data = load_instance(file_name)
grafo, nodos_estacion = create_graph(data)
#show_graph(grafo, data, nodos_estacion)

######################################################
# RESOLVER EL PROBLEMA Y MOSTRAR EL FLUJO RESULTANTE #
######################################################
cost, circulacion = solve_circulacion(grafo)
print("Costo de la circulación: ", cost)
#show_flow(grafo, circulacion, data, nodos_estacion)