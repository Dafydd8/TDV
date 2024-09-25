def mochilas_PD(capacidades, pesos, beneficios):
    dps = []
    for i in range(len(capacidades)):
        dp = []
        c = capacidades[i]
        for j in range(len(beneficios)+1):
            dp.append([0] * (c+1))
        dps.append(dp)


    for i in range(1, len(pesos)+1):
        for j in range(len(capacidades)):
            for k in range(1, capacidades[j]+1):
                if pesos[i-1] <= k:
                    # dp[i][c1][c2] = max(dp[i-1][c1][c2], dp[i-1][c1-pesos[i-1]][c2] + beneficios[i-1])
                    dps[j][i][k] = max(dps[j][i-1][k], dps[j][i-1][k-pesos[i-1]] + beneficios[i-1])
                else:
                    dps[j][i][k] = dps[j][i-1][k]
    
    maximo = 0
    for dp in dps:
        print(dp)
        print("hola")
        maximo = max(maximo, dp[-1][-1])

    return maximo

maquinas = [10, 10]
pesos = [5, 5, 6, 4, 1]
b = [5, 5, 5, 5, 1]


print(mochilas_PD(maquinas, pesos, b))