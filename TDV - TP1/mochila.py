def suma(s, pesos):
    rv = 0
    for i in range(len(s)):
        rv += pesos[i] * s[i]
    return rv 



b = []
def mochila(c, pesos, beneficios, s):
 
    global b
    if len(s) == len(pesos):
        if suma(s, pesos) <= c and suma(s, beneficios) > suma(b, beneficios):
            b = s.copy()

            
        return suma(b, beneficios)
    else:
        s_aux = s[:] + [1]
        b1 = mochila(c, pesos, beneficios, s_aux)
        s_aux1 = s[:] + [0]
        b2 = mochila(c, pesos, beneficios, s_aux1)
        return max(b1, b2)
    
def mochila_sinB(c, pesos, beneficios, s):
    if len(s) == len(pesos):
        if suma(s, pesos) <= c:     
            return suma(s, beneficios)
        else:
            return 0
    else:
        s_aux = s[:] + [1]
        b1 = mochila_sinB(c, pesos, beneficios, s_aux)
        s_aux1 = s[:] + [0]
        b2 = mochila_sinB(c, pesos, beneficios, s_aux1)
        return max(b1, b2)
    
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

def reconstruccion(dp, i, j, pesos):
    rv = []
    while(i > 0 and j > 0):
        sin = dp[i-1][j]
        if dp[i][j] == sin:
            i -= 1
        else:
            j -= pesos[i-1]
            i -= 1
            rv.append(i)
    return rv


pesos = [2, 3, 4, 5]
beneficios = [3, 4, 5, 6]
b, dp = mochila_PD(len(pesos), 10, pesos, beneficios)
print(b)
print(reconstruccion(dp, len(pesos), 10, pesos))
#print(mochila_sinB(10, [2, 3, 4, 5], [3, 4, 5, 6], []))
#print(b)

