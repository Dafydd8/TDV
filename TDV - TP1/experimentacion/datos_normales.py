import numpy as np
import random

# Generar 10,000 datos con una media de 5 y desviación estándar de 2
pesos_normales = np.random.normal(500, 250, 20)
benef_normales = np.random.normal(500, 250, 20)
pesos = []
benef = []

for i in range(len(pesos_normales)):
    pesos.append(int(pesos_normales[i]))
    benef.append(int(benef_normales[i]))


#benef_c = [98]
#for i in range(10):
#    benef_c.append(benef_c[-1] + random.randint(1, 200))

print(pesos)
print(benef)
