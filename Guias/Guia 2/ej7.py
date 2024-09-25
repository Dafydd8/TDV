import time

def sumasDistintas(n):
    if n == 1:
        return 1
    elif n == 2:
        return 1# hay una forma de escribir 2: (1+1)
    elif n == 3:
        return 2 # hay dos formas de escribir 3: (1+1+1),(3)
    elif n == 4:
        return 4# hay cuatro formas de escribir 4: (1+1+1+1),(1+3)(3+1),(4)
    else:
        return sumasDistintas(n-1) + sumasDistintas(n-3) + sumasDistintas(n-4)


def formas_sumar(n, nros):
    if n == 0:
        return 1
    if n < min(nros):
        return 0
    else:
        rv = 0
        for nro in nros:
            if nro <= n:
                rv += formas_sumar(n - nro, nros)
        return rv
    
def formas_sumar_dp(n, nros):
    dp = [0] * (n+1)
    dp[0] = 1
    for i in range(1, n+1):
        for nro in nros:
            if i>= nro:
                dp[i] += dp[i-nro]
    return dp[n]

t1 = []
t2 = []
t3 = []

for i in range(1, 47, 5):
    print(i)
    a = time.perf_counter()
    sumasDistintas(i)
    b = time.perf_counter()
    t1.append(b-a)

    #a = time.perf_counter()
    #formas_sumar(i, [1,3,4])
    #b = time.perf_counter()
    #t2.append(b-a)

    a = time.perf_counter()
    formas_sumar_dp(i, [1,3,4])
    b = time.perf_counter()
    t3.append(b-a)

f = open("tiempos2.csv", "w")
f.write("n,ellos,dp\n")
for i in range(len(t1)):
    print(i)
    #f.write(f"{2*i+1},{t1[i]},{t2[i]},{t3[i]}\n")
    f.write(f"{5*i+1},{t1[i]},{t3[i]}\n")
    