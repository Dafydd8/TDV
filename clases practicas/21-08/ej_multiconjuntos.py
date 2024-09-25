def suma_multiconjunto(i, m, k):
    if len(m) == i and k == 0:
        return 1
    if len(m) == i:
        return 0
    return suma_multiconjunto(i+1, m, k) + suma_multiconjunto(i+1, m, k-m[i])

print(suma_multiconjunto(0, [1,2,3], 3))
    