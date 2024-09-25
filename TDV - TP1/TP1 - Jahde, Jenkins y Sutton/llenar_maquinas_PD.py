# FUNCIONES AUXILIARES
def suma_capacidades(capacidades): # funcion que retorna la suma de las capacidades actuales de las maquinas
    rv = 0
    for i in capacidades:
        rv += i
    return rv

# IMPLEMENTACION DE LOS ALGORITMOS
def llenar_maquinas_pd(item, capacidades, pesos, beneficios, dp): # funcion que llena las maquinas con programacion dinamica
    if item == 0: # caso base
        clave = (0, tuple(capacidades))
        dp[clave] = 0
        return 0
    
    else: # caso recursivo
        if (item, tuple(capacidades)) in dp:
            return dp[(item, tuple(capacidades))]

        sin = llenar_maquinas_pd(item-1, capacidades, pesos, beneficios,dp) # caso sin incluir el item
        en_i = 0
        for m in range(len(capacidades)): # caso incluyendo el item para cada maquina m
            if pesos[item-1] <= capacidades[m]:
                nuevas_capacidades = capacidades[:]
                nuevas_capacidades[m] -= pesos[item-1]
                en_i = max(en_i, beneficios[item-1] + llenar_maquinas_pd(item-1, nuevas_capacidades, pesos, beneficios,dp))
        dp[(item, tuple(capacidades))] = max(sin, en_i) # guardamos el maximo en el diccionario
        return max(sin, en_i)

def reconstruir(dp, i, capacidades, pesos, beneficios): # funcion que reconstruye la solucion a partir del diccionario dp
    rv = []
    while(i > 0 and suma_capacidades(capacidades) > 0): # mientras haya items y las maquinas no esten vacias
        clave = (i-1, tuple(capacidades))
        if clave in dp and dp[clave] == dp[(i, tuple(capacidades))]: # si el valor de dp en la clave anterior es igual al actual
            i -= 1
            rv.append(0)
    
        else:
            for m in range(1, len(capacidades)+1): # buscamos la maquina en la que se incluyo el item
                if pesos[i-1] <= capacidades[m-1]:
                    nuevas_capacidades = capacidades[:]
                    nuevas_capacidades[m-1] -= pesos[i-1]
                    n = beneficios[i-1] + dp[(i-1, tuple(nuevas_capacidades))]
                    if dp[(i, tuple(capacidades))] == n:
                        capacidades = nuevas_capacidades
                        rv.append(m)
                        i -= 1
                        break
                
    while(i > 0): # si quedan items por incluir y las maquinas no tienen más capacidad
        rv.append(0)
        i -= 1

    return rv[::-1]