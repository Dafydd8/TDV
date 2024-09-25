import pandas as pd
import matplotlib.pyplot as plt

# Cargar los datos de los archivos CSV
pesosA_2M = pd.read_csv('pesosA_2M.csv')
pesosA_4M = pd.read_csv('pesosA_4M.csv')

# Calcular los promedios para cada algoritmo en ambos datasets
algoritmos = ['FB', 'FACT', 'OPT', 'PD']
promedios_2M = [pesosA_2M[alg].mean() for alg in algoritmos]
promedios_4M = [pesosA_4M[alg].mean() for alg in algoritmos]

# Crear el gráfico de barras
fig, ax = plt.subplots(figsize=(10, 6))

# Posiciones en el eje X para los algoritmos
x = range(len(algoritmos))

# Crear las barras
ax.bar(x, promedios_2M, width=0.4, label='2M', align='center', color='blue')
ax.bar([i + 0.4 for i in x], promedios_4M, width=0.4, label='4M', align='center', color='gray')

# Configurar las etiquetas y el título
ax.set_xlabel('Algoritmos')
ax.set_ylabel('Tiempo promedio (ms)')
ax.set_title('Comparación de tiempos promedio - Pesos altos (2M vs 4M)')
ax.set_xticks([i + 0.2 for i in x])
ax.set_xticklabels(algoritmos)
ax.legend()

# Mostrar el gráfico
plt.tight_layout()
plt.show()
