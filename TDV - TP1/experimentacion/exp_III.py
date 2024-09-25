import matplotlib.pyplot as plt
import csv

# Abrir el archivo CSV
f = open("no_fit.csv", "r", encoding="utf-8")
t_FB = []
t_fact = []
t_opt = []
t_pd = []

data = dict()

for linea in csv.DictReader(f):
    t_FB.append(float(linea["FB"]))
    t_opt.append(float(linea["OPT"]))
    t_fact.append(float(linea["FACT"]))
    t_pd.append(float(linea["PD"]))

data["FB"] = t_FB
data["OPT"] = t_opt
data["FACT"] = t_fact
data["PD"] = t_fact

labels = list(data.keys())
values = list(data.values())

print(labels)

# Crear boxplot
plt.boxplot(values, labels=labels)

# Agregar título y etiquetas
plt.title('Tiempo de ejecución por algoritmo')
plt.xlabel('Algoritmos')
plt.ylabel('Tiempo de ejecución (ms)')

# Mostrar el gráfico
plt.show()