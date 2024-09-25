def dp_max(dp, i, capacidades_restantes, beneficios, pesos):
    n = len(pesos)
    m = len(capacidades_restantes)
    if i == n:  # Si no quedan objetos
        return 0

    # Crear una tupla como clave para el estado actual
    estado = tuple(capacidades_restantes)
    if (i, estado) in dp:  # Si ya se ha calculado este estado
        return dp[(i, estado)]
    
    # Opción 1: No usar el objeto i
    max_valor = dp_max(dp, i + 1, capacidades_restantes, beneficios, pesos)
    
    # Opción 2: Intentar usar el objeto en alguna de las mochilas
    for j in range(m):
        if capacidades_restantes[j] >= pesos[i]:
            nuevas_capacidades = list(capacidades_restantes)
            nuevas_capacidades[j] -= pesos[i]
            # Calcular el nuevo valor incluyendo el objeto en la mochila j
            max_valor = max(max_valor, dp_max(dp, i + 1, nuevas_capacidades, beneficios, pesos) + beneficios[i])
    
    # Guardar el resultado en la tabla DP
    dp[(i, estado)] = max_valor
    return max_valor


dp = {}
maquinas = [10, 10]
pesos = [5, 5, 6, 4, 1]
b = [5, 5, 5, 5, 1]


print(dp_max(dp, 0, maquinas, b, pesos))