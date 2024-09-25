#El problema a resolver es: Dadas dos cadenas s y t, queremos transformar s en t.
#Las operaciones permitidas son: sustituir un caracter por otro, eliminar un caracter y agregar un caracter. 
#Queremos encontrar la cantidad minima de operaciones necesarias para transformar s en t.

def editDistance_TD(s, t , i , j, dp): # i es index de s, j es index de t, toma una dp llena de -1
    if i == 0 or j == 0:
        dp[i][j] = max(i, j)
        return dp[i][j]
    if dp[i][j] != -1:
        return dp[i][j]
    sustituir = editDistance_TD(s, t, i - 1, j - 1, dp) + int((s[i-1] != t[j-1]))
    eliminar = editDistance_TD(s, t, i - 1, j, dp) + 1
    agregar = editDistance_TD(s, t, i, j - 1, dp) + 1
    dp[i][j] = min(sustituir, eliminar, agregar)
    return dp[i][j]

def editDistance_BU(s, t, dp): #este toma una dp vacia vacia y la arma desde 0
    dp.append([])
    for i in range(len(t)+1):
        dp[0].append(i)
    for i in range(1, len(s)+1):
        dp.append([i])
        for j in range(1, len(t)+1):
            sustituir = dp[i-1][j-1] + int((s[i-1] != t[j-1]))
            eliminar = dp[i-1][j] + 1
            agregar = dp[i][j-1] + 1
            dp[i].append(min(sustituir, eliminar, agregar))
    return dp[len(s)][len(t)]

def reconstruir(dp) -> str:
    rv = ""
    i = len(dp)-1
    j = len(dp[0])-1
    while i > 0 and j > 0:
        sustituir = dp[i-1][j-1] + int((s[i-1] != t[j-1]))
        eliminar = dp[i-1][j] + 1
        if dp[i][j] == sustituir:
            rv += "\\"
            i -= 1
            j -= 1
        elif dp[i][j] == eliminar:
            rv += "|"
            i -= 1
        else:
            rv += "-"
            j -= 1
    while i > 0:
        rv += "|"
        i -= 1
    while j > 0:
        rv += "-"
        j -= 1
    return rv[::-1]

dp = []
dp2 = []
s = "atagctg"
t = "ctaga"
for i in range(len(s)+1):
    linea = []
    for j in range(len(t)+1):
        linea.append(-1)
    dp.append(linea)

#print(editDistance_TD(s, t, len(s), len(t), dp))
print(editDistance_BU(s, t, dp2))
print(dp2)
print(reconstruir(dp2))
