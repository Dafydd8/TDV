def pesos_ok(s, pesos_m, pesos_i):
    solucs = dict()
    for i in range(len(s)):
        if s[i] in solucs:
            solucs[s[i]] += pesos_i[i]
        else:
            solucs[s[i]] = pesos_i[i]
    solucs.pop(0, None)
    for clave in solucs:
        if solucs[clave] > pesos_m[clave-1]:
            return False
    return True

def suma_beneficios(s, beneficios):
    rv = 0
    for i in range(len(s)):
        if s[i] != 0:
            rv += beneficios[i]
    return rv

a = 0
def llenar_maquinas_FB(beneficios, pesos_i, pesos_m, s):
    global a
    a+=1
    if len(s) == len(beneficios):
        if pesos_ok(s, pesos_m, pesos_i):     
            return suma_beneficios(s, beneficios)
        else:
            return 0
    else: 
        valores = []
        for i in range(len(pesos_m)+1):
            s_aux = s[:] + [i]
            valores.append(llenar_maquinas_FB(beneficios, pesos_i, pesos_m, s_aux))
        rv = max(valores)   
        return max(valores)  
    
maquinas = [10, 10]
pesos = [5, 5, 6, 4, 1]
beneficios = [5, 5, 5, 5, 1]

print(llenar_maquinas_FB(beneficios, pesos, maquinas, []))
print("a = ", a)