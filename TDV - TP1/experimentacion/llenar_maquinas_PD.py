def suma_capacidades(capacidades):
    rv = 0
    for i in capacidades:
        rv += i
    return rv

def llenar_maquinas_pd(item, capacidades, pesos, beneficios, dp):
    if item == 0:
        clave = (0, tuple(capacidades))
        dp[clave] = 0
        return 0
    
    else:
        if (item, tuple(capacidades)) in dp:
            return dp[(item, tuple(capacidades))]

        sin = llenar_maquinas_pd(item-1, capacidades, pesos, beneficios,dp)
        en_i = 0
        for m in range(len(capacidades)):
            if pesos[item-1] <= capacidades[m]:
                nuevas_capacidades = capacidades[:]
                nuevas_capacidades[m] -= pesos[item-1]
                en_i = max(en_i, beneficios[item-1] + llenar_maquinas_pd(item-1, nuevas_capacidades, pesos, beneficios,dp))
        dp[(item, tuple(capacidades))] = max(sin, en_i)
        return max(sin, en_i)

def reconstruir(dp, i, capacidades, pesos, beneficios):
    rv = []
    while(i > 0 and suma_capacidades(capacidades) > 0):
        clave = (i-1, tuple(capacidades))
        if clave in dp and dp[clave] == dp[(i, tuple(capacidades))]:
            i -= 1
            rv.append(0)
    
        else:
            for m in range(1, len(capacidades)+1):
                if pesos[i-1] <= capacidades[m-1]:
                    nuevas_capacidades = capacidades[:]
                    nuevas_capacidades[m-1] -= pesos[i-1]
                    n = beneficios[i-1] + dp[(i-1, tuple(nuevas_capacidades))]
                    if dp[(i, tuple(capacidades))] == n:
                        capacidades = nuevas_capacidades
                        rv.append(m)
                        i -= 1
                        break
                
    while(i > 0):
        rv.append(0)
        i -= 1

    return rv[::-1]

maquinas = [10, 10]
pesos = [5, 5, 6, 4, 1]
b = [5, 5, 5, 5, 1]
dp = dict()

print(llenar_maquinas_pd(len(pesos), maquinas, pesos, b, dp))

print(reconstruir(dp, len(pesos), maquinas, pesos, b))