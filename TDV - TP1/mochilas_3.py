def mochila_2(k, c, pesos, beneficios):
    if k == 0 or c == 0:
        return 0
    else:
        b_sin = mochila_2(k-1, c, pesos, beneficios)
        b_con = 0
        if pesos[k-1] <= c:
            b_con = beneficios[k-1] + mochila_2(k-1, c - pesos[k-1], pesos, beneficios)
        return max(b_sin, b_con)

def mochila_PD(k, c, pesos, beneficios):
    dp = []
    for i in range(k+1):
        dp.append([0] * (c+1))
    for i in range(1,k+1):
        for j in range(1,c+1):
            if pesos[i-1] <= j:
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-pesos[i-1]] + beneficios[i-1])
            else:
                dp[i][j] = dp[i-1][j]

    return dp[k][c], dp

a = 0
def mochilas(item, capacidades, pesos, beneficios, dp):
    global a
    a += 1
    if item == 0:
        return 0
    
    else:
        if (item, tuple(capacidades)) in dp:
            return dp[(item, tuple(capacidades))]

        sin = mochilas(item-1, capacidades, pesos, beneficios,dp)
        en_i = 0
        for m in range(len(capacidades)):
            if pesos[item-1] <= capacidades[m]:
                nuevas_capacidades = capacidades[:]
                nuevas_capacidades[m] -= pesos[item-1]
                en_i = max(en_i, beneficios[item-1] + mochilas(item-1, nuevas_capacidades, pesos, beneficios,dp))
        dp[(item, tuple(capacidades))] = max(sin, en_i)
        return max(sin, en_i)
    
c = 0
def mochilas_bruto(item, capacidades, pesos, beneficios):
    global c
    c += 1
    if item == 0:
        return 0
    
    else:
        sin = mochilas_bruto(item-1, capacidades, pesos, beneficios)
        en_i = 0
        for m in range(len(capacidades)):
            if pesos[item-1] <= capacidades[m]:
                nuevas_capacidades = capacidades[:]
                nuevas_capacidades[m] -= pesos[item-1]
                en_i = max(en_i, beneficios[item-1] + mochilas_bruto(item-1, nuevas_capacidades, pesos, beneficios))
        return max(sin, en_i)

maquinas = [10, 10]
pesos = [5, 5, 6, 4, 1]
b = [5, 5, 5, 5, 1]
dp = dict()

print(mochilas(len(pesos), maquinas, pesos, b, dp))
for clave in dp:
    print(clave, dp[clave])
print(a)

print(mochilas_bruto(len(pesos), maquinas, pesos, b))
print(c)