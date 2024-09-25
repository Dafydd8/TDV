import pandas as pd
import matplotlib.pyplot as plt

# Leer los archivos CSV
cpp_5 = pd.read_csv("Cpp_20.csv")
py_5 = pd.read_csv("Py_20.csv")

# Calcular las medias de las columnas '4M' y '2M'
media_cpp_4M = cpp_5["4M"].mean()
media_cpp_2M = cpp_5["2M"].mean()

media_py_4M = py_5["4M"].mean()
media_py_2M = py_5["2M"].mean()

# Datos para el gráfico
condiciones = ['4M', '2M']
medias_cpp = [media_cpp_4M, media_cpp_2M]
medias_py = [media_py_4M, media_py_2M]

# Crear gráfico de barras
bar_width = 0.35
x = range(len(condiciones))

plt.bar(x, medias_cpp, width=bar_width, label='C++', color='#b67fc7', align='center')
plt.bar([i + bar_width for i in x], medias_py, width=bar_width, label='Python', color='#67c7d6', align='center')

# Agregar etiquetas y título
plt.xlabel('Cantidad de máquinas')
plt.ylabel('Tiempo de ejecución promedio (ms)')
plt.title('C++ VS Python - 20 instancias')

# Agregar leyenda
plt.xticks([i + bar_width / 2 for i in x], condiciones)
plt.legend()

# Mostrar gráfico
plt.show()
