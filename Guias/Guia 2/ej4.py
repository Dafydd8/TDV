#AUXILIARES
def cant_camiones(solucion):
    set_solucion = set(solucion)
    return len(set_solucion)

def suma_pesos(s, pesos):
    rv = 0
    for i in range(len(s)):
        if s[i] != 0:
            rv += pesos[i]
    return rv

def puedo_meter(maquina, capacidad, pesos, solucion):
    for i in range(len(solucion)):
        if solucion[i] == maquina:
            capacidad -= pesos[i]
    return capacidad >= pesos[len(solucion)]

#------- Ejercicio 4 -------
def camiones(capacidades, pesos, solucion):
    global best
    if len(solucion) == len(pesos):
        if (suma_pesos(solucion, pesos) > suma_pesos(best, pesos)) or (cant_camiones(solucion) < cant_camiones(best) and suma_pesos(solucion, pesos) == suma_pesos(best, pesos)):
            best = solucion.copy()
            return suma_pesos(solucion, pesos)
        else:
            return 0
    valores = []
    for i in range(len(capacidades)+1):
        if (i == 0) or (puedo_meter(i, capacidades[i-1], pesos, solucion)):
            solucion_aux = solucion[:] + [i]
            peso = camiones(capacidades, pesos, solucion_aux)
            valores.append(peso)
    return max(valores)
        
best = []
capacidades = [10, 10, 10]
pesos = [4,6,6,4]
s = []
print(camiones(capacidades, pesos, s))
print(best)
