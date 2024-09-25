import matplotlib.pyplot as plt
import csv

# Abrir el archivo CSV y leer los datos
with open("tiempos2.csv", "r", encoding="utf-8") as f:
    i_vals = []
    t_ellos = []
    #t_recursivo = []
    t_dp = []


    # Leer el CSV
    for linea in csv.DictReader(f):
        i_vals.append(int(linea["n"]))
        t_ellos.append(float(linea["ellos"]))
        #t_recursivo.append(float(linea["recursivo"]))
        t_dp.append(float(linea["dp"]))

# Crear el gráfico
plt.plot(i_vals, t_ellos, label="ellos", marker="o")
#plt.plot(i_vals, t_recursivo, label="recu", marker="s")
plt.plot(i_vals, t_dp, label="dp", marker="^")

# Agregar título y etiquetas
plt.title('Tiempo de ejecución en función n')
plt.xlabel('N')
plt.ylabel('tiempo de ejecución (s)')

# Mostrar leyenda
plt.legend()

# Mostrar el gráfico
plt.show()
