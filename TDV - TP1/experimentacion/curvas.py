import matplotlib.pyplot as plt
import csv

# Abrir el archivo CSV y leer los datos
with open("varia_n_2M.csv", "r", encoding="utf-8") as f:
    i_vals = []
    t_FB = []
    t_FACT = []
    t_OPT = []
    t_PD = []

    # Leer el CSV
    for linea in csv.DictReader(f):
        i_vals.append(int(linea["i"]))        # Columna 'i' como tamaño de entrada
        t_FB.append(float(linea["FB"]))       # Columna 'FB' como tiempos de FB
        t_FACT.append(float(linea["FACT"]))   # Columna 'FACT' como tiempos de FACT
        t_OPT.append(float(linea["OPT"]))     # Columna 'OPT' como tiempos de OPT
        t_PD.append(float(linea["PD"]))       # Columna 'PD' como tiempos de PD

# Crear el gráfico
plt.plot(i_vals, t_FB, label="FB", marker="o")
plt.plot(i_vals, t_FACT, label="FACT", marker="s")
plt.plot(i_vals, t_OPT, label="OPT", marker="^")
plt.plot(i_vals, t_PD, label="PD", marker="d")

# Agregar título y etiquetas
plt.title('Tiempo de ejecución en función de cantidad de instancias - Pesos bajos')
plt.xlabel('Cantidad de instancias')
plt.ylabel('Tiempo de ejecución (ms)')

# Mostrar leyenda
plt.legend()

# Mostrar el gráfico
plt.show()
